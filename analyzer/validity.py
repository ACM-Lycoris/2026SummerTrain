"""Infer whether a C++ source file contains a substantive solution."""

from __future__ import annotations

import re


def _mask_comments_and_literals(text: str) -> str:
    """Replace comments and literal contents with spaces while preserving lines."""
    result: list[str] = []
    index = 0
    state = "code"
    quote = ""
    while index < len(text):
        char = text[index]
        nxt = text[index + 1] if index + 1 < len(text) else ""
        if state == "code":
            if char == "/" and nxt == "/":
                result.extend((" ", " "))
                index += 2
                state = "line_comment"
                continue
            if char == "/" and nxt == "*":
                result.extend((" ", " "))
                index += 2
                state = "block_comment"
                continue
            if char in {'"', "'"}:
                quote = char
                result.append(char)
                index += 1
                state = "literal"
                continue
            result.append(char)
            index += 1
            continue
        if state == "line_comment":
            if char == "\n":
                result.append("\n")
                state = "code"
            else:
                result.append(" ")
            index += 1
            continue
        if state == "block_comment":
            if char == "*" and nxt == "/":
                result.extend((" ", " "))
                index += 2
                state = "code"
                continue
            result.append("\n" if char == "\n" else " ")
            index += 1
            continue
        if char == "\\" and index + 1 < len(text):
            result.append(" ")
            escaped = text[index + 1]
            result.append("\n" if escaped == "\n" else " ")
            index += 2
            continue
        if char == quote:
            result.append(char)
            index += 1
            state = "code"
            continue
        result.append("\n" if char == "\n" else " ")
        index += 1
    return "".join(result)


def _main_body(masked: str) -> str | None:
    match = re.search(r"\bmain\s*\([^)]*\)\s*\{", masked)
    if not match:
        return None
    opening = masked.find("{", match.start())
    depth = 0
    for index in range(opening, len(masked)):
        if masked[index] == "{":
            depth += 1
        elif masked[index] == "}":
            depth -= 1
            if depth == 0:
                return masked[opening + 1 : index]
    return masked[opening + 1 :]


def _remove_boilerplate(body: str) -> str:
    patterns = (
        r"(?:std::)?ios(?:::sync_with_stdio)?\s*\(\s*false\s*\)\s*;",
        r"(?:std::)?cin\.tie\s*\(\s*(?:nullptr|NULL|0)\s*\)\s*;",
        r"(?:std::)?cout\.tie\s*\(\s*(?:nullptr|NULL|0)\s*\)\s*;",
        r"return\s+0\s*;",
    )
    remaining = body
    for pattern in patterns:
        remaining = re.sub(pattern, " ", remaining)
    return remaining


def analyze_source(text: str) -> dict[str, object]:
    """Return line metrics and a conservative solution-completeness inference."""
    masked = _mask_comments_and_literals(text)
    line_count = len(text.splitlines())
    code_line_count = sum(1 for line in masked.splitlines() if line.strip())
    if not masked.strip():
        reason = "empty"
    else:
        body = _main_body(masked)
        if body is None:
            reason = "missing_main"
        elif re.search(r"[A-Za-z0-9_]", _remove_boilerplate(body)):
            reason = "substantive"
        else:
            reason = "template_only"
    return {
        "line_count": line_count,
        "code_line_count": code_line_count,
        "valid_code": reason == "substantive",
        "validity_reason": reason,
    }
