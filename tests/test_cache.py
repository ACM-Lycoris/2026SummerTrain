import hashlib
import tempfile
import unittest
from pathlib import Path

from analyzer.storage import analyze_with_cache, enrich_snapshot


class CacheTests(unittest.TestCase):
    def test_same_fingerprint_reuses_cached_analysis(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source_path = root / "1" / "A.cpp"
            source_path.parent.mkdir()
            text = "int main(){int n; cin>>n; cout<<n;}"
            source_path.write_text(text, encoding="utf-8")
            fingerprint = hashlib.sha256(source_path.read_bytes()).hexdigest()
            record = {"path": "1/A.cpp", "sha256": fingerprint, "valid_code": True}
            cache = {
                "files": {
                    "1/A.cpp": {
                        "sha256": fingerprint,
                        "algorithm_tags": [{"tag": "Cached", "evidence": []}],
                        "quality_findings": [],
                    }
                }
            }

            result = analyze_with_cache(record, root, cache)

            self.assertEqual(result["algorithm_tags"][0]["tag"], "Cached")

    def test_changed_fingerprint_recomputes_and_replaces_cache(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source_path = root / "1" / "A.cpp"
            source_path.parent.mkdir()
            source_path.write_text("int main(){vector<int> dp(3); dp[1]=dp[0];}", encoding="utf-8")
            fingerprint = hashlib.sha256(source_path.read_bytes()).hexdigest()
            record = {"path": "1/A.cpp", "sha256": fingerprint, "valid_code": True}
            cache = {
                "files": {
                    "1/A.cpp": {
                        "sha256": "old",
                        "algorithm_tags": [{"tag": "Cached", "evidence": []}],
                        "quality_findings": [],
                    }
                }
            }

            result = analyze_with_cache(record, root, cache)

            self.assertEqual(result["algorithm_tags"][0]["tag"], "DP")
            self.assertEqual(cache["files"]["1/A.cpp"]["sha256"], fingerprint)

    def test_invalid_problem_gets_incomplete_finding(self):
        snapshot = {
            "sessions": [
                {
                    "problems": [
                        {
                            "valid_code": False,
                            "files": [
                                {
                                    "path": "9/E.cpp",
                                    "sha256": "x",
                                    "valid_code": False,
                                    "validity_reason": "template_only",
                                }
                            ],
                        }
                    ]
                }
            ]
        }

        enrich_snapshot(snapshot, Path("."), {"files": {}})

        problem = snapshot["sessions"][0]["problems"][0]
        self.assertEqual(problem["algorithm_tags"], [])
        self.assertEqual(problem["quality_findings"][0]["rule_id"], "CPP000_INCOMPLETE")


if __name__ == "__main__":
    unittest.main()
