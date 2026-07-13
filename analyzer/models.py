"""Small shared helpers for stable analyzer records."""

from __future__ import annotations


def problem_sort_key(problem: dict[str, object]) -> tuple[int, str]:
    problem_id = str(problem["problem_id"])
    return (0 if problem_id.isalpha() else 1, problem_id)

