"""Validated JSON persistence for inferred training data."""

from __future__ import annotations

import json
import os
import tempfile
from datetime import date, datetime
from pathlib import Path

from analyzer.classification import classify_algorithms
from analyzer.quality import analyze_quality
from analyzer.scanner import scan_training_root


EMPTY_OVERRIDES = {"schema_version": 1, "problems": {}, "sessions": {}}


def load_overrides(path: Path) -> dict:
    path = Path(path)
    if not path.exists():
        return {"schema_version": 1, "problems": {}, "sessions": {}}
    try:
        value = json.loads(path.read_text(encoding="utf-8-sig"))
    except (OSError, json.JSONDecodeError) as error:
        raise ValueError(f"无法读取人工覆盖文件 {path}: {error}") from error
    if not isinstance(value, dict) or value.get("schema_version") != 1:
        raise ValueError("人工覆盖文件 schema_version 必须为 1")
    problems = value.get("problems", {})
    sessions = value.get("sessions", {})
    if not isinstance(problems, dict) or not isinstance(sessions, dict):
        raise ValueError("人工覆盖文件的 problems 和 sessions 必须是对象")
    for key, override in problems.items():
        if not isinstance(override, dict) or override.get("status") not in {"AC", "ATTEMPTED"}:
            raise ValueError(f"{key} 的人工状态只能是 AC 或 ATTEMPTED")
    for key, override in sessions.items():
        if not str(key).isdigit() or not isinstance(override, dict):
            raise ValueError(f"无效的场次覆盖键: {key}")
        if "date" in override:
            try:
                date.fromisoformat(override["date"])
            except (TypeError, ValueError) as error:
                raise ValueError(f"场次 {key} 的 date 必须是 YYYY-MM-DD") from error
    return {"schema_version": 1, "problems": problems, "sessions": sessions}


def write_json_atomic(path: Path, value: object) -> None:
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary_name: str | None = None
    try:
        with tempfile.NamedTemporaryFile(
            mode="w",
            encoding="utf-8",
            newline="\n",
            prefix=f".{path.stem}-",
            suffix=".tmp",
            dir=path.parent,
            delete=False,
        ) as temporary:
            temporary_name = temporary.name
            json.dump(value, temporary, ensure_ascii=False, indent=2)
            temporary.write("\n")
            temporary.flush()
            os.fsync(temporary.fileno())
        Path(temporary_name).replace(path)
    finally:
        if temporary_name:
            Path(temporary_name).unlink(missing_ok=True)


def build_snapshot(root: Path, overrides_path: Path) -> dict:
    root = Path(root).resolve()
    overrides = load_overrides(overrides_path)
    return {
        "schema_version": 1,
        "generated_at": datetime.now().astimezone().isoformat(timespec="seconds"),
        "training_root": ".",
        "sessions": scan_training_root(root, overrides),
    }


def _read_analysis_text(path: Path) -> str:
    try:
        return path.read_text(encoding="utf-8-sig")
    except UnicodeDecodeError:
        return path.read_text(encoding="gb18030")


def analyze_with_cache(file_record: dict, root: Path, cache: dict) -> dict:
    files_cache = cache.setdefault("files", {})
    relative_path = str(file_record["path"])
    cached = files_cache.get(relative_path)
    if cached and cached.get("sha256") == file_record.get("sha256"):
        return {
            "algorithm_tags": cached.get("algorithm_tags", []),
            "quality_findings": cached.get("quality_findings", []),
        }
    if not file_record.get("valid_code"):
        result = {
            "algorithm_tags": [],
            "quality_findings": [
                {
                    "rule_id": "CPP000_INCOMPLETE",
                    "severity": "high",
                    "path": relative_path,
                    "line": 1,
                    "message": f"源码被判定为 {file_record.get('validity_reason', 'incomplete')}，尚无完整解题逻辑。",
                    "suggestion": "补全实现后重新运行分析。",
                }
            ],
        }
    else:
        text = _read_analysis_text(Path(root) / Path(relative_path))
        result = {
            "algorithm_tags": classify_algorithms(text),
            "quality_findings": analyze_quality(text, relative_path),
        }
    files_cache[relative_path] = {"sha256": file_record.get("sha256"), **result}
    return result


def enrich_snapshot(snapshot: dict, root: Path, cache: dict) -> dict:
    """Attach cached per-file analysis and aggregate it at problem level."""
    for session in snapshot.get("sessions", []):
        for problem in session.get("problems", []):
            tag_evidence: dict[str, list[str]] = {}
            quality_findings: list[dict] = []
            for file_record in problem.get("files", []):
                analysis = analyze_with_cache(file_record, root, cache)
                file_record.update(analysis)
                for tag in analysis["algorithm_tags"]:
                    if tag["tag"] == "未分类" and tag_evidence:
                        continue
                    target = tag_evidence.setdefault(tag["tag"], [])
                    for evidence in tag.get("evidence", []):
                        if evidence not in target:
                            target.append(evidence)
                quality_findings.extend(analysis["quality_findings"])
            if len(tag_evidence) > 1:
                tag_evidence.pop("未分类", None)
            problem["algorithm_tags"] = [
                {"tag": tag, "evidence": evidence}
                for tag, evidence in tag_evidence.items()
            ]
            problem["quality_findings"] = sorted(
                quality_findings,
                key=lambda finding: (
                    finding["path"], finding["line"], finding["rule_id"]
                ),
            )
    return snapshot
