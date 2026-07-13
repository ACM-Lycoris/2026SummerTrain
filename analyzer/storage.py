"""Validated JSON persistence for inferred training data."""

from __future__ import annotations

import json
import os
import tempfile
from datetime import date, datetime
from pathlib import Path

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
