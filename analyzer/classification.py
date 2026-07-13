"""Explainable, deterministic algorithm classification for C++ sources."""

from __future__ import annotations

import re


TAG_ORDER = ("DP", "贪心", "图论", "数据结构", "字符串", "数学", "几何", "二分")


def _has(text: str, pattern: str) -> bool:
    return re.search(pattern, text, flags=re.IGNORECASE | re.MULTILINE) is not None


def classify_algorithms(text: str) -> list[dict[str, object]]:
    evidence: dict[str, list[str]] = {tag: [] for tag in TAG_ORDER}

    if _has(text, r"\bdp\w*\s*\[") and _has(text, r"\bdp\w*\s*\[[^]]+\]\s*="):
        evidence["DP"].append("检测到 DP 数组及状态赋值")

    has_sort = _has(text, r"\b(?:std::)?sort\s*\(")
    has_priority_queue = _has(text, r"\bpriority_queue\s*<")
    has_accumulating_loop = _has(text, r"\b(?:for|while)\s*\(") and _has(
        text, r"\b(?:ans|sum\w*|res)\s*(?:\+=|=\s*(?:min|max)\s*\()"
    )
    if has_sort and (has_priority_queue or has_accumulating_loop):
        evidence["贪心"].append("排序后进行局部选择或累计")

    graph_signals = []
    if _has(text, r"\b(?:bfs|dfs)\b"):
        graph_signals.append("BFS/DFS 遍历")
    if _has(text, r"\bqueue\s*<") and _has(text, r"\.(?:push|pop)\s*\("):
        graph_signals.append("队列式遍历")
    if _has(text, r"\b(?:find|union|merge)\w*\s*\(") and _has(text, r"\bfa\s*\["):
        graph_signals.append("并查集")
    if _has(text, r"\b(?:dijkstra|floyd|spfa)\b"):
        graph_signals.append("最短路")
    if _has(text, r"vector\s*<\s*vector\s*<") and _has(text, r"\b(?:edge|adj|graph|g)\b"):
        graph_signals.append("邻接结构")
    evidence["图论"].extend(graph_signals)

    structures = (
        (r"\bpriority_queue\s*<", "优先队列"),
        (r"\bqueue\s*<", "队列"),
        (r"\bstack\s*<", "栈"),
        (r"\b(?:unordered_)?set\s*<", "集合"),
        (r"\b(?:unordered_)?map\s*<", "映射"),
        (r"\b(?:segment\w*|fenwick|lowbit)\b", "树状/线段结构"),
    )
    for pattern, label in structures:
        if _has(text, pattern):
            evidence["数据结构"].append(label)

    if _has(text, r"\bstring\b") and _has(
        text,
        r"\b(?:prefix\w*|kmp\w*|trie\w*|hash\w*|substr|find|reverse)\b|\.substr\s*\(",
    ):
        evidence["字符串"].append("字符串及匹配/变换操作")

    math_signals = (
        (r"\b(?:qpow|quickpow|fastpow|gcd|lcm)\b", "快速幂或整除算法"),
        (r"\bMOD\b|%\s*(?:MOD|mod|p)\b", "模运算"),
        (r"\b(?:prime|factor|fac|invfac|comb)\w*\b", "质因数或组合计数"),
    )
    for pattern, label in math_signals:
        if _has(text, pattern):
            evidence["数学"].append(label)

    explicit_geometry = _has(text, r"\bPoint\b|\b(?:cross|polygon|convex_hull)\b")
    area_with_coordinates = _has(text, r"\b\w*area\w*\b") and _has(
        text, r"\bdx\b[\s\S]{0,200}\bdy\b|\bdy\b[\s\S]{0,200}\bdx\b"
    )
    if explicit_geometry or area_with_coordinates:
        evidence["几何"].append("点、距离、叉积或面积计算")

    if _has(text, r"while\s*\(\s*\w+\s*<\s*\w+\s*\)") and _has(
        text, r"\bmid\b"
    ) and _has(text, r"\bcheck\s*\("):
        evidence["二分"].append("边界循环、mid 与 check 判定")

    result = [
        {"tag": tag, "evidence": evidence[tag]}
        for tag in TAG_ORDER
        if evidence[tag]
    ]
    return result or [{"tag": "未分类", "evidence": []}]
