import os
import tempfile
import unittest
from datetime import datetime
from pathlib import Path

from analyzer.scanner import normalize_problem_id, scan_training_root


SOLUTION = "int main(){int n; std::cin>>n; std::cout<<n; return 0;}\n"
TEMPLATE = "int main(){return 0;}\n"


class ScannerTests(unittest.TestCase):
    def test_problem_id_normalizes_case_and_variants(self):
        self.assertEqual(normalize_problem_id("i.cpp"), ("I", None))
        self.assertEqual(normalize_problem_id("C(DSUbfs).cpp"), ("C", None))
        problem_id, warning = normalize_problem_id("123.cpp")
        self.assertEqual(problem_id, "123")
        self.assertEqual(warning, "unrecognized_problem_id")

    def test_scans_only_top_level_cpp_files_in_numbered_directories(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "1" / ".cph").mkdir(parents=True)
            (root / "data").mkdir()
            (root / "1" / "A.cpp").write_text(SOLUTION, encoding="utf-8")
            (root / "1" / "B.CPP").write_text(SOLUTION, encoding="utf-8")
            (root / "1" / ".cph" / "C.cpp").write_text(SOLUTION, encoding="utf-8")
            (root / "data" / "D.cpp").write_text(SOLUTION, encoding="utf-8")

            sessions = scan_training_root(root)

            self.assertEqual([session["session_id"] for session in sessions], [1])
            self.assertEqual(
                [problem["problem_id"] for problem in sessions[0]["problems"]],
                ["A", "B"],
            )

    def test_groups_variants_and_any_valid_version_makes_problem_ac(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "2").mkdir()
            (root / "2" / "C(DSUbfs).cpp").write_text(TEMPLATE, encoding="utf-8")
            (root / "2" / "C(setBFS).cpp").write_text(SOLUTION, encoding="utf-8")

            session = scan_training_root(root)[0]
            problem = session["problems"][0]

            self.assertEqual(problem["problem_id"], "C")
            self.assertEqual(problem["status"], "AC")
            self.assertEqual(problem["source"], "inferred")
            self.assertEqual(problem["inferred_status"], "AC")
            self.assertEqual(len(problem["files"]), 2)
            self.assertTrue(problem["valid_code"])

    def test_uses_latest_source_modification_date_for_session(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            session_dir = root / "10"
            session_dir.mkdir()
            first = session_dir / "A.cpp"
            last = session_dir / "B.cpp"
            first.write_text(SOLUTION, encoding="utf-8")
            last.write_text(TEMPLATE, encoding="utf-8")
            first_time = datetime(2026, 7, 12, 22, 30).timestamp()
            last_time = datetime(2026, 7, 13, 9, 15).timestamp()
            os.utime(first, (first_time, first_time))
            os.utime(last, (last_time, last_time))

            session = scan_training_root(root)[0]

            self.assertEqual(session["date"], "2026-07-13")
            self.assertTrue(session["started_at"].startswith("2026-07-12T22:30"))
            self.assertTrue(session["ended_at"].startswith("2026-07-13T09:15"))
            self.assertEqual(session["problem_count"], 2)
            self.assertEqual(session["ac_count"], 1)
            self.assertEqual(session["attempted_count"], 1)


if __name__ == "__main__":
    unittest.main()
