"""Conservative, evidence-located C++ risk checks."""

from __future__ import annotations

import re

from analyzer.validity import _mask_comments_and_literals


SEVERITY_ORDER = {"high": 0, "medium": 1, "low": 2}


def _line_number(text: str, offset: int) -> int:
    return text.count("\n", 0, offset) + 1


def _finding(
    rule_id: str,
    severity: str,
    path: str,
    line: int,
    message: str,
    suggestion: str,
) -> dict[str, object]:
    return {
        "rule_id": rule_id,
        "severity": severity,
        "path": path,
        "line": line,
        "message": message,
        "suggestion": suggestion,
    }


def _matching_brace(text: str, opening: int) -> int | None:
    depth = 0
    for index in range(opening, len(text)):
        if text[index] == "{":
            depth += 1
        elif text[index] == "}":
            depth -= 1
            if depth == 0:
                return index
    return None


def analyze_quality(text: str, path: str) -> list[dict[str, object]]:
    findings: list[dict[str, object]] = []

    for match in re.finditer(r"\b[A-Za-z_]\w*\s*\[\s*([1-9]\d*)\s*\]", text):
        findings.append(
            _finding(
                "CPP001_FIXED_SUBSCRIPT",
                "medium",
                path,
                _line_number(text, match.start()),
                "固定下标访问在容器较短时可能越界。",
                "访问前确认输入约束或显式检查容器长度。",
            )
        )

    map_names = set(
        re.findall(r"\b(?:unordered_)?map\s*<[^;\n]+>\s*([A-Za-z_]\w*)", text)
    )
    for name in map_names:
        pattern = rf"\b(?:if|while)\s*\([^)]*\b{re.escape(name)}\s*\[[^]]+\]"
        for match in re.finditer(pattern, text):
            findings.append(
                _finding(
                    "CPP002_MAP_IMPLICIT_INSERT",
                    "medium",
                    path,
                    _line_number(text, match.start()),
                    f"条件中读取 {name}[key] 可能隐式插入不存在的键。",
                    "只读判断优先使用 count、find 或 contains。",
                )
            )

    structural_text = _mask_comments_and_literals(text)
    for outer in re.finditer(r"\bfor\s*\([^)]*\)\s*\{", structural_text):
        opening = structural_text.find("{", outer.start(), outer.end())
        closing = _matching_brace(structural_text, opening)
        if closing is None:
            continue
        inner = re.search(r"\bfor\s*\(", structural_text[opening + 1 : closing])
        if inner:
            offset = opening + 1 + inner.start()
            findings.append(
                _finding(
                    "CPP003_NESTED_LOOP",
                    "medium",
                    path,
                    _line_number(text, offset),
                    "嵌套循环可能形成 O(n²) 或 O(nm) 时间复杂度。",
                    "结合最大输入规模核对操作次数，必要时改用预处理或更合适的数据结构。",
                )
            )

    function_match = re.search(r"\b(?:void|int|long\s+long|bool)\s+(DFS|dfs)\s*\([^)]*\)\s*\{", text)
    if function_match:
        recursive = re.search(
            rf"\b{function_match.group(1)}\s*\(", text[function_match.end() :]
        )
        if recursive:
            offset = function_match.end() + recursive.start()
            findings.append(
                _finding(
                    "CPP004_RECURSIVE_DFS",
                    "medium",
                    path,
                    _line_number(text, offset),
                    "递归 DFS 在深链或大网格上可能导致栈溢出。",
                    "核对最大深度；深度可能很大时改用显式栈。",
                )
            )

    for match in re.finditer(r"\b(?:pi|PI)\b\s*=\s*(3\.\d+)", text):
        literal = match.group(1)
        if len(literal.split(".", 1)[1]) < 8:
            findings.append(
                _finding(
                    "CPP005_PI_PRECISION",
                    "low",
                    path,
                    _line_number(text, match.start()),
                    "圆周率常量精度较低，可能放大浮点误差。",
                    "使用 std::numbers::pi 或 acos(-1.0)。",
                )
            )

    runtime_dp = re.compile(
        r"\bvector\s*<[^;\n]+>\s+(?:d|n)?dp\w*\s*\(\s*(?!\d+\b)([A-Za-z_]\w*)"
    )
    for match in runtime_dp.finditer(text):
        findings.append(
            _finding(
                "CPP006_RUNTIME_DP",
                "low",
                path,
                _line_number(text, match.start()),
                f"DP 容量由运行时变量 {match.group(1)} 决定，可能存在内存或时间风险。",
                "根据约束估算状态数和字节数，并确认转移复杂度。",
            )
        )

    unique: dict[tuple[str, int], dict[str, object]] = {}
    for finding in findings:
        unique[(str(finding["rule_id"]), int(finding["line"]))] = finding
    return sorted(
        unique.values(),
        key=lambda finding: (
            SEVERITY_ORDER[str(finding["severity"])],
            str(finding["path"]),
            int(finding["line"]),
            str(finding["rule_id"]),
        ),
    )
