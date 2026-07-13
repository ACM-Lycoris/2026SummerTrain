"""Discover numbered ACM sessions and infer problem completion."""

from __future__ import annotations

import hashlib
import re
from datetime import datetime
from pathlib import Path

from analyzer.models import problem_sort_key
from analyzer.validity import analyze_source


def normalize_problem_id(filename: str) -> tuple[str, str | None]:
    stem = Path(filename).stem
    match = re.match(r"([A-Za-z]+)", stem)
    if match:
        return match.group(1).upper(), None
    return stem.upper(), "unrecognized_problem_id"


def _local_iso(timestamp: float) -> str:
    return datetime.fromtimestamp(timestamp).astimezone().isoformat(timespec="seconds")


def _read_source(path: Path) -> tuple[str, str | None]:
    try:
        return path.read_text(encoding="utf-8-sig"), None
    except UnicodeDecodeError:
        try:
            return path.read_text(encoding="gb18030"), None
        except (OSError, UnicodeError) as error:
            return "", f"read_error: {error}"
    except OSError as error:
        return "", f"read_error: {error}"


def _source_record(root: Path, session_id: int, path: Path) -> tuple[dict, list[str]]:
    text, read_warning = _read_source(path)
    metrics = analyze_source(text)
    problem_id, id_warning = normalize_problem_id(path.name)
    relative_path = path.relative_to(root).as_posix()
    record = {
        "path": relative_path,
        "session_id": session_id,
        "filename": path.name,
        "original_problem_id": path.stem,
        "problem_id": problem_id,
        "modified_at": _local_iso(path.stat().st_mtime),
        "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
        **metrics,
    }
    warnings = []
    if id_warning:
        warnings.append(f"{relative_path}: {id_warning}")
    if read_warning:
        record["valid_code"] = False
        record["validity_reason"] = "read_error"
        warnings.append(f"{relative_path}: {read_warning}")
    return record, warnings


def _apply_problem_override(problem: dict, session_id: int, overrides: dict) -> None:
    override = overrides.get("problems", {}).get(f"{session_id}/{problem['problem_id']}")
    if not override:
        return
    problem["status"] = override["status"]
    problem["source"] = "manual"
    if override.get("note"):
        problem["note"] = override["note"]


def scan_training_root(root: Path, overrides: dict | None = None) -> list[dict]:
    """Scan direct C++ children of numeric session directories."""
    root = Path(root).resolve()
    overrides = overrides or {"problems": {}, "sessions": {}}
    session_directories = sorted(
        (path for path in root.iterdir() if path.is_dir() and re.fullmatch(r"\d+", path.name)),
        key=lambda path: int(path.name),
    )
    sessions: list[dict] = []
    for session_directory in session_directories:
        session_id = int(session_directory.name)
        cpp_files = sorted(
            (
                path
                for path in session_directory.iterdir()
                if path.is_file() and path.suffix.lower() == ".cpp"
            ),
            key=lambda path: path.name.casefold(),
        )
        if not cpp_files:
            continue
        grouped: dict[str, list[dict]] = {}
        warnings: list[str] = []
        for cpp_file in cpp_files:
            file_record, file_warnings = _source_record(root, session_id, cpp_file)
            grouped.setdefault(str(file_record["problem_id"]), []).append(file_record)
            warnings.extend(file_warnings)
        problems: list[dict] = []
        for problem_id, files in grouped.items():
            valid_code = any(bool(file["valid_code"]) for file in files)
            inferred_status = "AC" if valid_code else "ATTEMPTED"
            problem = {
                "problem_id": problem_id,
                "status": inferred_status,
                "source": "inferred",
                "inferred_status": inferred_status,
                "valid_code": valid_code,
                "files": files,
                "algorithm_tags": [],
                "quality_findings": [],
            }
            _apply_problem_override(problem, session_id, overrides)
            problems.append(problem)
        problems.sort(key=problem_sort_key)
        timestamps = [file["modified_at"] for problem in problems for file in problem["files"]]
        started_at = min(timestamps)
        ended_at = max(timestamps)
        session_override = overrides.get("sessions", {}).get(str(session_id), {})
        date = session_override.get("date", ended_at[:10])
        sessions.append(
            {
                "session_id": session_id,
                "directory": session_directory.relative_to(root).as_posix(),
                "date": date,
                "started_at": started_at,
                "ended_at": ended_at,
                "problem_count": len(problems),
                "ac_count": sum(problem["status"] == "AC" for problem in problems),
                "attempted_count": sum(problem["status"] == "ATTEMPTED" for problem in problems),
                "problems": problems,
                "warnings": warnings,
            }
        )
    return sessions
