# ACM Postmortem MVP Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a dependency-free Python tool that infers the training database from the numbered C++ directories and generates an evidence-based daily review report.

**Architecture:** The numbered directories remain read-only inputs. Focused analyzer modules produce a deterministic JSON snapshot, merge a separately owned manual override file, cache code analysis by SHA-256, and render one idempotent Markdown report per training date.

**Tech Stack:** Python 3.11+ standard library, `unittest`, JSON, Markdown, existing C++ source files.

## Global Constraints

- Never modify, move, compile, or rename files inside numbered training directories.
- Treat a complete saved C++ solution as `AC / inferred`; treat empty, template-only, or clearly incomplete code as `ATTEMPTED / inferred`.
- A manual override always wins and is never rewritten by automatic scanning.
- Merge multiple filenames for the same normalized session/problem into one problem record while preserving every source version.
- Use only Python standard-library runtime dependencies.
- Re-running scan and report commands must not duplicate data or reports.

---

## File Map

- `analyzer/models.py`: typed dictionary constructors and stable serialization helpers.
- `analyzer/validity.py`: comment-aware C++ line counting and completeness inference.
- `analyzer/scanner.py`: numbered-directory discovery, problem normalization, source metadata, grouping, and status inference.
- `analyzer/storage.py`: override validation, atomic JSON writes, snapshot assembly, and cache persistence.
- `analyzer/classification.py`: explainable multi-label algorithm detection.
- `analyzer/quality.py`: evidence-located C++ risk rules.
- `analyzer/profile.py`: aggregate strengths, weaknesses, and evidence-based review suggestions.
- `analyzer/report.py`: deterministic Markdown report rendering.
- `main.py`: command-line orchestration.
- `tests/`: isolated standard-library tests for every public behavior.
- `config/settings.json`: recent-window and scanner defaults.
- `data/manual_overrides.json`: user-owned empty override seed.
- `data/sessions.json`: generated initial database.
- `data/analysis_cache.json`: generated fingerprint cache.
- `reports/YYYY-MM-DD.md`: generated historical report.
- `README.md`: daily one-click and CLI instructions.

### Task 1: Source discovery, validity inference, and snapshot storage

**Files:**
- Create: `analyzer/__init__.py`
- Create: `analyzer/models.py`
- Create: `analyzer/validity.py`
- Create: `analyzer/scanner.py`
- Create: `analyzer/storage.py`
- Create: `tests/__init__.py`
- Create: `tests/test_validity.py`
- Create: `tests/test_scanner.py`
- Create: `tests/test_storage.py`

**Interfaces:**
- Produces: `analyze_source(text: str) -> dict[str, object]` with `line_count`, `code_line_count`, `valid_code`, and `validity_reason`.
- Produces: `normalize_problem_id(filename: str) -> tuple[str, str | None]`.
- Produces: `scan_training_root(root: Path, overrides: dict | None = None) -> list[dict]`.
- Produces: `load_overrides(path: Path) -> dict`, `write_json_atomic(path: Path, value: object) -> None`, and `build_snapshot(root: Path, overrides_path: Path) -> dict`.

- [ ] **Step 1: Write failing validity tests**

```python
class ValidityTests(unittest.TestCase):
    def test_empty_source_is_attempted(self):
        result = analyze_source("\n// comment\n")
        self.assertFalse(result["valid_code"])
        self.assertEqual(result["validity_reason"], "empty")

    def test_template_only_main_is_attempted(self):
        source = "#include <bits/stdc++.h>\nint main(){return 0;}\n"
        self.assertEqual(analyze_source(source)["validity_reason"], "template_only")

    def test_solution_with_input_and_output_is_valid(self):
        source = "int main(){int n; std::cin>>n; std::cout<<n+1; return 0;}"
        self.assertTrue(analyze_source(source)["valid_code"])
```

- [ ] **Step 2: Run validity tests and confirm RED**

Run: `python -m unittest tests.test_validity -v`
Expected: import failure because `analyzer.validity` does not exist.

- [ ] **Step 3: Implement minimal comment-aware validity analysis**

Create lexical helpers that replace comments and quoted literals without changing line numbers, count physical and non-comment code lines, extract the balanced `main` body, remove known boilerplate statements, and classify `empty`, `missing_main`, `template_only`, or `substantive`.

- [ ] **Step 4: Run validity tests and confirm GREEN**

Run: `python -m unittest tests.test_validity -v`
Expected: 3 tests pass.

- [ ] **Step 5: Write failing scanner tests**

Tests create temporary `1/`, `2/`, `data/`, and nested `.cph/` directories; assert only top-level C++ sources in numeric directories are scanned, `i.cpp` becomes `I`, both `C(DSUbfs).cpp` and `C(setBFS).cpp` form one `C` problem, any valid version makes it AC, and modification times populate ISO timestamps and the latest local date.

- [ ] **Step 6: Run scanner tests and confirm RED**

Run: `python -m unittest tests.test_scanner -v`
Expected: import failure because `analyzer.scanner` does not exist.

- [ ] **Step 7: Implement deterministic scanner and problem grouping**

Use `Path.iterdir()`, a full numeric directory regex, case-insensitive `.cpp` filtering, SHA-256, stable numeric/session and problem sorting, paths relative to the root, and one warning for unrecognized problem IDs.

- [ ] **Step 8: Run scanner tests and confirm GREEN**

Run: `python -m unittest tests.test_scanner -v`
Expected: all scanner tests pass.

- [ ] **Step 9: Write failing storage and override tests**

Tests assert missing overrides return the schema-1 empty structure, valid `10/J` overrides change final status/source but retain inferred status, invalid status raises `ValueError`, a session date override wins, and atomic JSON output parses after replacement.

- [ ] **Step 10: Run storage tests and confirm RED**

Run: `python -m unittest tests.test_storage -v`
Expected: import failure because `analyzer.storage` does not exist.

- [ ] **Step 11: Implement validated overrides and atomic snapshot writes**

Validate exact status values `AC` and `ATTEMPTED`, accept schema version 1, merge only recognized problem/session keys, preserve manual notes, expose the inferred status, and use `NamedTemporaryFile` plus `Path.replace` in the destination directory.

- [ ] **Step 12: Run the complete Task 1 suite**

Run: `python -m unittest tests.test_validity tests.test_scanner tests.test_storage -v`
Expected: all tests pass with no warnings or tracebacks.

### Task 2: Explainable algorithm and C++ quality analysis with caching

**Files:**
- Create: `analyzer/classification.py`
- Create: `analyzer/quality.py`
- Modify: `analyzer/storage.py`
- Create: `tests/test_classification.py`
- Create: `tests/test_quality.py`
- Create: `tests/test_cache.py`

**Interfaces:**
- Produces: `classify_algorithms(text: str) -> list[dict[str, object]]`, each item containing `tag` and `evidence`.
- Produces: `analyze_quality(text: str, path: str) -> list[dict[str, object]]`, each item containing `rule_id`, `severity`, `path`, `line`, `message`, and `suggestion`.
- Produces: `analyze_with_cache(file_record: dict, root: Path, cache: dict) -> dict` and updated cache entries keyed by relative path plus fingerprint.

- [ ] **Step 1: Write failing classification tests**

Add real snippets for DP transition, BFS queue traversal, DSU, priority-queue scheduling, binary search with `check`, modular fast power, string prefix function, and geometry area. Assert evidence accompanies every detected tag and an unrelated trivial program returns `未分类`.

- [ ] **Step 2: Run classification tests and confirm RED**

Run: `python -m unittest tests.test_classification -v`
Expected: import failure because the classifier does not exist.

- [ ] **Step 3: Implement ordered evidence rules**

Use compiled, named regex evidence groups and a fixed output order: `DP`, `贪心`, `图论`, `数据结构`, `字符串`, `数学`, `几何`, `二分`, then `未分类`. Require paired evidence for ambiguous tags such as greedy.

- [ ] **Step 4: Run classification tests and confirm GREEN**

Run: `python -m unittest tests.test_classification -v`
Expected: all classification tests pass.

- [ ] **Step 5: Write failing quality-rule tests**

Cover these high-signal MVP rules with line assertions and counterexamples: constant vector/string subscript, `map[key]` used in a condition, nested input-sized loops, recursive DFS, approximate pi constant, DP allocation from runtime capacity, and a clean simple program.

- [ ] **Step 6: Run quality tests and confirm RED**

Run: `python -m unittest tests.test_quality -v`
Expected: import failure because the quality analyzer does not exist.

- [ ] **Step 7: Implement evidence-located risk rules**

Keep rules line-oriented and conservative; messages must say “可能” where a heuristic cannot prove a bug. Deduplicate by `(rule_id, line)` and sort by severity, path, line, and rule ID.

- [ ] **Step 8: Run quality tests and confirm GREEN**

Run: `python -m unittest tests.test_quality -v`
Expected: all quality tests pass.

- [ ] **Step 9: Write failing cache tests**

Create a temporary source record and cache, assert the first call populates results, the same fingerprint reuses stored results, and a changed fingerprint recomputes and replaces the entry.

- [ ] **Step 10: Run cache tests and confirm RED**

Run: `python -m unittest tests.test_cache -v`
Expected: failure because cached analysis is not implemented.

- [ ] **Step 11: Implement fingerprint cache integration**

Cache only derived `algorithm_tags` and `quality_findings`; never cache inferred/manual status. Invalid source versions receive no algorithm tags and a template finding rather than normal risk analysis.

- [ ] **Step 12: Run the complete Task 2 suite**

Run: `python -m unittest tests.test_classification tests.test_quality tests.test_cache -v`
Expected: all tests pass.

### Task 3: Capability profile, specific suggestions, reports, and CLI

**Files:**
- Create: `analyzer/profile.py`
- Create: `analyzer/report.py`
- Create: `main.py`
- Create: `tests/test_profile.py`
- Create: `tests/test_report.py`
- Create: `tests/test_cli.py`

**Interfaces:**
- Produces: `build_profile(sessions: list[dict], recent_days: int) -> dict` with `strengths`, `weaknesses`, `distribution`, and `suggestions`.
- Produces: `render_daily_report(snapshot: dict, target_date: str, recent_days: int = 7) -> str`.
- Produces: `main(argv: list[str] | None = None) -> int` supporting `--root`, `--date`, and `--scan-only`.

- [ ] **Step 1: Write failing profile tests**

Build small in-memory histories that assert repeated AC evidence can create a strength, attempted or repeated-risk evidence creates a weakness, and every review suggestion names a date, session, problem, and trigger. Assert no generic suggestion is emitted when evidence is absent.

- [ ] **Step 2: Run profile tests and confirm RED**

Run: `python -m unittest tests.test_profile -v`
Expected: import failure because `analyzer.profile` does not exist.

- [ ] **Step 3: Implement transparent profile thresholds**

A strength requires at least two AC problems carrying the tag and no repeated high-severity finding. Weaknesses rank attempted evidence before repeated rule IDs, then under-covered tags with historical failure evidence. Suggestions reuse those exact evidence records and cap output at three.

- [ ] **Step 4: Run profile tests and confirm GREEN**

Run: `python -m unittest tests.test_profile -v`
Expected: all profile tests pass.

- [ ] **Step 5: Write failing report tests**

Assert all seven Chinese sections appear, AC and attempted IDs are correct, recent distribution is present, quality findings include paths/lines, evidence-based suggestions are rendered, missing unseen contest problems are disclosed, and rendering the same snapshot twice is byte-identical.

- [ ] **Step 6: Run report tests and confirm RED**

Run: `python -m unittest tests.test_report -v`
Expected: import failure because `analyzer.report` does not exist.

- [ ] **Step 7: Implement deterministic Markdown rendering**

Render `# YYYY-MM-DD 训练复盘` plus the approved sections. Group all sessions on the target date, calculate completion counts from effective statuses, and use explicit “暂无具体证据” text instead of generic advice.

- [ ] **Step 8: Run report tests and confirm GREEN**

Run: `python -m unittest tests.test_report -v`
Expected: all report tests pass.

- [ ] **Step 9: Write failing CLI integration tests**

In a temporary root, invoke `main(["--root", root, "--scan-only"])` and assert JSON files are created without a report; invoke without `--scan-only` and assert the latest-date report exists; request a missing date and assert a nonzero return.

- [ ] **Step 10: Run CLI tests and confirm RED**

Run: `python -m unittest tests.test_cli -v`
Expected: import failure or assertion failure because CLI orchestration is absent.

- [ ] **Step 11: Implement the CLI orchestration**

Use `argparse`, default root to the directory containing `main.py`, create missing generated directories, seed only a missing override/config file, rebuild snapshot and cache atomically, choose the latest session date by default, and return concise Chinese errors on stderr.

- [ ] **Step 12: Run the complete Task 3 suite**

Run: `python -m unittest tests.test_profile tests.test_report tests.test_cli -v`
Expected: all tests pass.

### Task 4: Daily entry point, documentation, real import, and acceptance verification

**Files:**
- Create: `config/settings.json`
- Create: `data/manual_overrides.json`
- Create: `run-review.cmd`
- Create: `README.md`
- Generate: `data/sessions.json`
- Generate: `data/analysis_cache.json`
- Generate: `reports/2026-07-13.md`

**Interfaces:**
- Consumes: `main.py` CLI from Task 3.
- Produces: double-clickable `run-review.cmd` that runs `py -3 main.py`, falls back to `python main.py`, preserves the exit code, and pauses so feedback remains visible.

- [ ] **Step 1: Add an integration assertion for the daily launcher contract**

Extend `tests/test_cli.py` to assert the committed launcher contains both Windows Python commands, forwards no destructive arguments, and invokes `pause` after execution.

- [ ] **Step 2: Run the launcher test and confirm RED**

Run: `python -m unittest tests.test_cli -v`
Expected: failure because `run-review.cmd` does not exist.

- [ ] **Step 3: Add minimal configuration, launcher, and README**

Set `recent_training_days` to 7, seed schema-1 empty overrides, document double-click and CLI usage, explain inferred/manual status and the missing contest-roster limitation, and list generated files.

- [ ] **Step 4: Run all automated tests**

Run: `python -m unittest discover -s tests -v`
Expected: all tests pass with no failures or errors.

- [ ] **Step 5: Generate the real initial database without changing training files**

Before scanning, record `git status --short` and SHA-256 hashes for all numbered-directory C++ files. Run `python main.py --scan-only`, parse `data/sessions.json`, and assert 10 sessions are present, session 2 groups both C variants under problem C, and `9/E.cpp` is `ATTEMPTED / inferred`.

- [ ] **Step 6: Generate and inspect the latest report**

Run: `python main.py --date 2026-07-13`.
Expected: `reports/2026-07-13.md` contains all approved sections and reports session 10 based on its latest modification date.

- [ ] **Step 7: Verify idempotency and raw-data preservation**

Hash generated JSON/report files, run the same date command again, and compare semantic JSON plus report bytes while allowing `generated_at` to change. Recompute numbered-directory C++ hashes and assert they exactly match Step 5.

- [ ] **Step 8: Run final syntax and repository checks**

Run: `python -m compileall -q analyzer main.py tests` and `git diff --check`.
Expected: both exit zero; `git status --short` shows only intended project/generated files plus the user's pre-existing untracked `9/` and `10/` data.
