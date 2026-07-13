import unittest

from analyzer.profile import build_profile


def problem(problem_id, status="AC", tags=(), findings=()):
    return {
        "problem_id": problem_id,
        "status": status,
        "algorithm_tags": [{"tag": tag, "evidence": ["test"]} for tag in tags],
        "quality_findings": list(findings),
    }


def session(session_id, date, problems):
    return {"session_id": session_id, "date": date, "problems": problems}


class ProfileTests(unittest.TestCase):
    def test_repeated_ac_tag_becomes_strength(self):
        sessions = [
            session(1, "2026-07-01", [problem("A", tags=("DP",))]),
            session(2, "2026-07-02", [problem("B", tags=("DP",))]),
        ]

        profile = build_profile(sessions, recent_days=7)

        self.assertEqual(profile["strengths"][0]["tag"], "DP")
        self.assertEqual(profile["strengths"][0]["ac_count"], 2)
        self.assertEqual(profile["distribution"]["DP"], 2)

    def test_attempted_problem_creates_specific_weakness_and_suggestion(self):
        sessions = [
            session(10, "2026-07-13", [problem("J", status="ATTEMPTED", tags=("几何",))])
        ]

        profile = build_profile(sessions, recent_days=7)

        self.assertEqual(profile["weaknesses"][0]["label"], "几何")
        suggestion = profile["suggestions"][0]
        self.assertEqual(suggestion["date"], "2026-07-13")
        self.assertEqual(suggestion["session_id"], 10)
        self.assertEqual(suggestion["problem_id"], "J")
        self.assertIn("未完成", suggestion["reason"])
        self.assertIn("几何", suggestion["action"])

    def test_repeated_quality_rule_has_priority_and_evidence(self):
        finding = {
            "rule_id": "CPP001_FIXED_SUBSCRIPT",
            "severity": "medium",
            "path": "1/A.cpp",
            "line": 8,
            "message": "固定下标可能越界。",
        }
        sessions = [
            session(1, "2026-07-01", [problem("A", findings=(finding,))]),
            session(2, "2026-07-02", [problem("B", findings=({**finding, "path": "2/B.cpp"},))]),
        ]

        profile = build_profile(sessions, recent_days=7)

        suggestion = profile["suggestions"][0]
        self.assertEqual(suggestion["date"], "2026-07-02")
        self.assertEqual(suggestion["session_id"], 2)
        self.assertEqual(suggestion["problem_id"], "B")
        self.assertIn("CPP001_FIXED_SUBSCRIPT", suggestion["reason"])

    def test_no_evidence_produces_no_generic_suggestion(self):
        profile = build_profile(
            [session(1, "2026-07-01", [problem("A", tags=("未分类",))])],
            recent_days=7,
        )

        self.assertEqual(profile["suggestions"], [])


if __name__ == "__main__":
    unittest.main()
