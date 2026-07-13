"""Command-line entry point for the ACM training postmortem tool."""

from __future__ import annotations

import argparse
import json
import os
import sys
import tempfile
from datetime import datetime
from pathlib import Path

from analyzer.report import render_daily_report
from analyzer.storage import build_snapshot, enrich_snapshot, write_json_atomic


DEFAULT_SETTINGS = {"schema_version": 1, "recent_training_days": 7}
DEFAULT_OVERRIDES = {"schema_version": 1, "problems": {}, "sessions": {}}


def _load_json(path: Path, default: dict) -> dict:
    if not path.exists():
        return dict(default)
    try:
        value = json.loads(path.read_text(encoding="utf-8-sig"))
    except (OSError, json.JSONDecodeError) as error:
        raise ValueError(f"无法读取 {path}: {error}") from error
    if not isinstance(value, dict):
        raise ValueError(f"{path} 的顶层必须是 JSON 对象")
    return value


def _write_text_atomic(path: Path, text: str) -> None:
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
            temporary.write(text)
            temporary.flush()
            os.fsync(temporary.fileno())
        Path(temporary_name).replace(path)
    finally:
        if temporary_name:
            Path(temporary_name).unlink(missing_ok=True)


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description="ACM 训练赛后分析工具")
    parser.add_argument(
        "--root",
        type=Path,
        default=Path(__file__).resolve().parent,
        help="训练根目录，默认是 main.py 所在目录",
    )
    parser.add_argument("--date", help="报告日期，格式 YYYY-MM-DD；默认取最新训练日期")
    parser.add_argument("--scan-only", action="store_true", help="只更新训练数据库，不生成报告")
    return parser


def main(argv: list[str] | None = None) -> int:
    args = _parser().parse_args(argv)
    root = args.root.resolve()
    data_directory = root / "data"
    config_path = root / "config" / "settings.json"
    overrides_path = data_directory / "manual_overrides.json"
    cache_path = data_directory / "analysis_cache.json"
    snapshot_path = data_directory / "sessions.json"
    try:
        if not config_path.exists():
            write_json_atomic(config_path, DEFAULT_SETTINGS)
        if not overrides_path.exists():
            write_json_atomic(overrides_path, DEFAULT_OVERRIDES)
        settings = _load_json(config_path, DEFAULT_SETTINGS)
        recent_days = int(settings.get("recent_training_days", 7))
        if recent_days < 1:
            raise ValueError("recent_training_days 必须大于 0")
        cache = _load_json(cache_path, {"schema_version": 1, "files": {}})
        cache.setdefault("schema_version", 1)
        cache.setdefault("files", {})

        snapshot = build_snapshot(root, overrides_path)
        if not snapshot["sessions"]:
            raise ValueError(f"{root} 中没有发现包含 C++ 文件的数字训练目录")
        enrich_snapshot(snapshot, root, cache)
        cache["generated_at"] = datetime.now().astimezone().isoformat(timespec="seconds")
        write_json_atomic(snapshot_path, snapshot)
        write_json_atomic(cache_path, cache)
        print(f"已更新训练数据库：{snapshot_path}")

        if args.scan_only:
            return 0
        target_date = args.date or max(session["date"] for session in snapshot["sessions"])
        report = render_daily_report(snapshot, target_date, recent_days)
        report_path = root / "reports" / f"{target_date}.md"
        _write_text_atomic(report_path, report)
        print(f"已生成训练复盘：{report_path}")
        return 0
    except (OSError, ValueError) as error:
        print(f"错误：{error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
