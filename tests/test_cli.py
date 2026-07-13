import json
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from io import StringIO
from pathlib import Path

from main import main


SOLUTION = "int main(){int n; std::cin>>n; std::cout<<n; return 0;}\n"


class CliTests(unittest.TestCase):
    def test_daily_launcher_has_python_fallback_and_pause(self):
        launcher = Path(__file__).resolve().parents[1] / "run-review.cmd"

        content = launcher.read_text(encoding="utf-8")

        self.assertIn("py -3 main.py", content)
        self.assertIn("python main.py", content)
        self.assertIn("pause", content.lower())
        self.assertNotIn(" del ", content.lower())

    def test_scan_only_creates_database_and_cache_without_report(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "1").mkdir()
            (root / "1" / "A.cpp").write_text(SOLUTION, encoding="utf-8")

            with redirect_stdout(StringIO()):
                exit_code = main(["--root", str(root), "--scan-only"])

            self.assertEqual(exit_code, 0)
            self.assertTrue((root / "data" / "sessions.json").exists())
            self.assertTrue((root / "data" / "analysis_cache.json").exists())
            self.assertTrue((root / "data" / "manual_overrides.json").exists())
            self.assertEqual(list((root / "reports").glob("*.md")), [])
            snapshot = json.loads((root / "data" / "sessions.json").read_text(encoding="utf-8"))
            self.assertEqual(snapshot["sessions"][0]["problems"][0]["status"], "AC")

    def test_default_run_writes_latest_date_report(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "1").mkdir()
            (root / "1" / "A.cpp").write_text(SOLUTION, encoding="utf-8")

            with redirect_stdout(StringIO()):
                exit_code = main(["--root", str(root)])

            self.assertEqual(exit_code, 0)
            reports = list((root / "reports").glob("*.md"))
            self.assertEqual(len(reports), 1)
            self.assertIn("今日训练总结", reports[0].read_text(encoding="utf-8"))

    def test_missing_requested_date_returns_nonzero(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "1").mkdir()
            (root / "1" / "A.cpp").write_text(SOLUTION, encoding="utf-8")
            errors = StringIO()

            with redirect_stdout(StringIO()), redirect_stderr(errors):
                exit_code = main(["--root", str(root), "--date", "1900-01-01"])

            self.assertNotEqual(exit_code, 0)
            self.assertIn("1900-01-01", errors.getvalue())

    def test_empty_training_root_returns_nonzero(self):
        with tempfile.TemporaryDirectory() as directory:
            errors = StringIO()

            with redirect_stderr(errors):
                exit_code = main(["--root", directory])

            self.assertNotEqual(exit_code, 0)
            self.assertIn("训练目录", errors.getvalue())


if __name__ == "__main__":
    unittest.main()
