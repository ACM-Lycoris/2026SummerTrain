"""Build an evidence-based training profile and review suggestions."""

from __future__ import annotations

from collections import Counter, defaultdict


def _problem_tags(problem: dict) -> list[str]:
    return [
        str(item["tag"])
        for item in problem.get("algorithm_tags", [])
        if item.get("tag") != "未分类"
    ]


def _recent_sessions(sessions: list[dict], recent_days: int) -> list[dict]:
    dates = sorted({session["date"] for session in sessions})
    selected_dates = set(dates[-max(1, recent_days) :])
    return [session for session in sessions if session["date"] in selected_dates]


def build_profile(sessions: list[dict], recent_days: int) -> dict:
    recent = _recent_sessions(sessions, recent_days) if sessions else []
    distribution: Counter[str] = Counter()
    ac_by_tag: dict[str, list[str]] = defaultdict(list)
    high_risk_by_tag: Counter[str] = Counter()
    attempted: list[dict] = []
    findings_by_rule: dict[str, list[dict]] = defaultdict(list)

    for session in sessions:
        for problem in session.get("problems", []):
            tags = _problem_tags(problem)
            reference = f"{session['date']} 第{session['session_id']}场 {problem['problem_id']}"
            if problem.get("status") == "AC":
                for tag in tags:
                    ac_by_tag[tag].append(reference)
            else:
                attempted.append(
                    {
                        "date": session["date"],
                        "session_id": session["session_id"],
                        "problem_id": problem["problem_id"],
                        "tags": tags,
                    }
                )
            for finding in problem.get("quality_findings", []):
                occurrence = {
                    "date": session["date"],
                    "session_id": session["session_id"],
                    "problem_id": problem["problem_id"],
                    **finding,
                }
                findings_by_rule[str(finding["rule_id"])].append(occurrence)
                if finding.get("severity") == "high":
                    for tag in tags:
                        high_risk_by_tag[tag] += 1

    for session in recent:
        for problem in session.get("problems", []):
            distribution.update(_problem_tags(problem))

    strengths = [
        {"tag": tag, "ac_count": len(references), "evidence": references[-3:]}
        for tag, references in ac_by_tag.items()
        if len(references) >= 2 and high_risk_by_tag[tag] < 2
    ]
    strengths.sort(key=lambda item: (-item["ac_count"], item["tag"]))

    weaknesses: list[dict] = []
    seen_weaknesses: set[tuple[str, str]] = set()
    for occurrence in sorted(
        attempted,
        key=lambda item: (item["date"], item["session_id"], item["problem_id"]),
        reverse=True,
    ):
        labels = occurrence["tags"] or ["未分类未完成题"]
        for label in labels:
            key = ("attempted", label)
            if key not in seen_weaknesses:
                weaknesses.append({"type": "attempted", "label": label, "evidence": occurrence})
                seen_weaknesses.add(key)
    repeated_rules = {
        rule_id: occurrences
        for rule_id, occurrences in findings_by_rule.items()
        if len(occurrences) >= 2
    }
    for rule_id, occurrences in sorted(
        repeated_rules.items(), key=lambda item: (-len(item[1]), item[0])
    ):
        weaknesses.append(
            {
                "type": "repeated_risk",
                "label": rule_id,
                "count": len(occurrences),
                "evidence": occurrences[-1],
            }
        )

    suggestions: list[dict] = []
    for rule_id, occurrences in sorted(
        repeated_rules.items(), key=lambda item: (-len(item[1]), item[0])
    ):
        latest = sorted(
            occurrences,
            key=lambda item: (item["date"], item["session_id"], item["problem_id"]),
        )[-1]
        suggestions.append(
            {
                "date": latest["date"],
                "session_id": latest["session_id"],
                "problem_id": latest["problem_id"],
                "reason": f"{rule_id} 已重复出现 {len(occurrences)} 次：{latest['message']}",
                "action": latest.get("suggestion")
                or f"复查 {latest.get('path', '')}:{latest.get('line', 1)} 的同类边界。",
            }
        )
    for occurrence in sorted(
        attempted,
        key=lambda item: (item["date"], item["session_id"], item["problem_id"]),
        reverse=True,
    ):
        label = "、".join(occurrence["tags"]) if occurrence["tags"] else "该题实现"
        suggestions.append(
            {
                "date": occurrence["date"],
                "session_id": occurrence["session_id"],
                "problem_id": occurrence["problem_id"],
                "reason": "该题状态为未完成（ATTEMPTED）。",
                "action": f"复盘 {label}，补全代码后用最小边界样例验证。",
            }
        )
    return {
        "strengths": strengths,
        "weaknesses": weaknesses,
        "distribution": dict(sorted(distribution.items())),
        "suggestions": suggestions[:3],
    }
