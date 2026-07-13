import json
import tempfile
import unittest
from pathlib import Path

from analyzer.storage import build_snapshot, load_overrides, write_json_atomic


SOLUTION = "int main(){int n; std::cin>>n; std::cout<<n; return 0;}\n"


class StorageTests(unittest.TestCase):
    def test_missing_overrides_returns_empty_schema(self):
        with tempfile.TemporaryDirectory() as directory:
            result = load_overrides(Path(directory) / "missing.json")

        self.assertEqual(result, {"schema_version": 1, "problems": {}, "sessions": {}})

    def test_manual_problem_status_wins_and_keeps_inferred_status(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "10").mkdir()
            (root / "10" / "J.cpp").write_text(SOLUTION, encoding="utf-8")
            overrides = root / "data" / "manual_overrides.json"
            write_json_atomic(
                overrides,
                {
                    "schema_version": 1,
                    "problems": {
                        "10/J": {"status": "ATTEMPTED", "note": "尚未通过"}
                    },
                    "sessions": {},
                },
            )

            problem = build_snapshot(root, overrides)["sessions"][0]["problems"][0]

            self.assertEqual(problem["inferred_status"], "AC")
            self.assertEqual(problem["status"], "ATTEMPTED")
            self.assertEqual(problem["source"], "manual")
            self.assertEqual(problem["note"], "尚未通过")

    def test_invalid_manual_status_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "overrides.json"
            path.write_text(
                json.dumps(
                    {
                        "schema_version": 1,
                        "problems": {"1/A": {"status": "WA"}},
                        "sessions": {},
                    }
                ),
                encoding="utf-8",
            )

            with self.assertRaisesRegex(ValueError, "AC.*ATTEMPTED"):
                load_overrides(path)

    def test_manual_session_date_wins(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "1").mkdir()
            (root / "1" / "A.cpp").write_text(SOLUTION, encoding="utf-8")
            overrides = root / "overrides.json"
            write_json_atomic(
                overrides,
                {
                    "schema_version": 1,
                    "problems": {},
                    "sessions": {"1": {"date": "2026-07-01"}},
                },
            )

            session = build_snapshot(root, overrides)["sessions"][0]

            self.assertEqual(session["date"], "2026-07-01")

    def test_atomic_json_output_is_parseable(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "nested" / "value.json"

            write_json_atomic(path, {"中文": [1, 2, 3]})

            self.assertEqual(json.loads(path.read_text(encoding="utf-8")), {"中文": [1, 2, 3]})
            self.assertEqual(list(path.parent.glob("*.tmp")), [])


if __name__ == "__main__":
    unittest.main()
