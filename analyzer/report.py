"""Render deterministic Markdown daily training reports."""

from __future__ import annotations

from collections import Counter

from analyzer.profile import build_profile


def _problem_label(session: dict, problem: dict, single_session: bool) -> str:
    return str(problem["problem_id"]) if single_session else f"{session['session_id']}/{problem['problem_id']}"


def render_daily_report(snapshot: dict, target_date: str, recent_days: int = 7) -> str:
    sessions = snapshot.get("sessions", [])
    today = [session for session in sessions if session.get("date") == target_date]
    if not today:
        raise ValueError(f"日期 {target_date} 没有训练记录")
    single_session = len(today) == 1
    completed: list[str] = []
    attempted: list[str] = []
    today_tags: Counter[str] = Counter()
    today_findings: list[tuple[dict, dict, dict]] = []
    for session in today:
        for problem in session.get("problems", []):
            label = _problem_label(session, problem, single_session)
            if problem.get("status") == "AC":
                completed.append(label)
            else:
                attempted.append(label)
            for tag in problem.get("algorithm_tags", []):
                if tag.get("tag") != "未分类":
                    today_tags[str(tag["tag"])] += 1
            for finding in problem.get("quality_findings", []):
                today_findings.append((session, problem, finding))

    profile = build_profile(sessions, recent_days)
    lines = [
        f"# {target_date} 训练复盘",
        "",
        "## 今日训练总结",
        "",
        f"今天记录了 {len(today)} 场训练、{len(completed) + len(attempted)} 道已发现题目，其中 {len(completed)} 道 AC，{len(attempted)} 道尚未完成。",
        "",
        "### 1. 完成情况",
        "",
        f"- AC 数量：{len(completed)}",
        f"- 已完成（AC）：{('、'.join(completed) if completed else '无')} ",
        f"- 未解决（ATTEMPTED）：{('、'.join(attempted) if attempted else '无')} ",
        "",
        "### 2. 算法分类",
        "",
        "今日标签：",
        "",
    ]
    if today_tags:
        lines.extend(f"- {tag}：{count}" for tag, count in sorted(today_tags.items()))
    else:
        lines.append("- 暂无足够代码证据进行分类")
    lines.extend(["", f"最近 {recent_days} 个训练日分布：", ""])
    distribution = profile["distribution"]
    if distribution:
        lines.extend(f"- {tag}：{count}" for tag, count in distribution.items())
    else:
        lines.append("- 暂无分类数据")

    lines.extend(["", "### 3. 代码质量分析", ""])
    if today_findings:
        for session, problem, finding in today_findings:
            lines.append(
                f"- [{finding['severity']}] `{finding['path']}:{finding['line']}` "
                f"（第 {session['session_id']} 场 {problem['problem_id']}，{finding['rule_id']}）："
                f"{finding['message']} 建议：{finding['suggestion']}"
            )
    else:
        lines.append("- 未发现当前规则能够定位的高信号风险。")

    lines.extend(["", "### 4. 能力画像", "", "当前优势：", ""])
    if profile["strengths"]:
        lines.extend(
            f"- {item['tag']}：累计 {item['ac_count']} 道 AC（证据：{'；'.join(item['evidence'])}）"
            for item in profile["strengths"]
        )
    else:
        lines.append("- 证据不足：同一标签至少需要 2 道 AC 才会列为优势。")
    lines.extend(["", "当前薄弱或待关注：", ""])
    if profile["weaknesses"]:
        for item in profile["weaknesses"]:
            evidence = item["evidence"]
            lines.append(
                f"- {item['label']}：来源 {evidence['date']} 第 {evidence['session_id']} 场 {evidence['problem_id']}"
            )
    else:
        lines.append("- 暂无失败或重复错误证据。")

    lines.extend(["", "### 5. 复习建议", ""])
    if profile["suggestions"]:
        for suggestion in profile["suggestions"]:
            lines.append(
                f"- {suggestion['date']} 第 {suggestion['session_id']} 场 {suggestion['problem_id']}："
                f"{suggestion['reason']} {suggestion['action']}"
            )
    else:
        lines.append("- 暂无具体历史证据，不生成泛泛建议。")

    warnings = [warning for session in today for warning in session.get("warnings", [])]
    lines.extend(
        [
            "",
            "### 6. 数据完整性说明",
            "",
            "- 当前目录没有比赛完整题目表，因此只能统计已创建源码的题目，无法统计从未创建源码的题目。",
            "- AC/ATTEMPTED 默认由源码完整性推断；`manual_overrides.json` 中的人工结论优先。",
        ]
    )
    lines.extend(f"- 扫描警告：{warning}" for warning in warnings)
    return "\n".join(line.rstrip() for line in lines) + "\n"
