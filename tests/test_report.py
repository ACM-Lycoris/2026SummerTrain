import unittest

from analyzer.report import render_daily_report


class ReportTests(unittest.TestCase):
    def setUp(self):
        self.snapshot = {
            "schema_version": 1,
            "sessions": [
                {
                    "session_id": 10,
                    "date": "2026-07-13",
                    "ac_count": 1,
                    "attempted_count": 1,
                    "problems": [
                        {
                            "problem_id": "A",
                            "status": "AC",
                            "algorithm_tags": [{"tag": "DP", "evidence": ["DP 数组"]}],
                            "quality_findings": [
                                {
                                    "rule_id": "CPP001_FIXED_SUBSCRIPT",
                                    "severity": "medium",
                                    "path": "10/A.cpp",
                                    "line": 12,
                                    "message": "固定下标访问可能越界。",
                                    "suggestion": "检查长度。",
                                }
                            ],
                        },
                        {
                            "problem_id": "B",
                            "status": "ATTEMPTED",
                            "algorithm_tags": [{"tag": "几何", "evidence": ["面积"]}],
                            "quality_findings": [],
                        },
                    ],
                }
            ],
        }

    def test_contains_all_approved_sections_and_completion_data(self):
        report = render_daily_report(self.snapshot, "2026-07-13")

        for section in (
            "## 今日训练总结",
            "### 1. 完成情况",
            "### 2. 算法分类",
            "### 3. 代码质量分析",
            "### 4. 能力画像",
            "### 5. 复习建议",
            "### 6. 数据完整性说明",
        ):
            self.assertIn(section, report)
        self.assertIn("已完成（AC）：A", report)
        self.assertIn("未解决（ATTEMPTED）：B", report)
        self.assertIn("AC 数量：1", report)

    def test_contains_distribution_quality_location_and_specific_suggestion(self):
        report = render_daily_report(self.snapshot, "2026-07-13")

        self.assertIn("DP：1", report)
        self.assertIn("10/A.cpp:12", report)
        self.assertIn("第 10 场 B", report)
        self.assertIn("几何", report)

    def test_discloses_missing_contest_roster(self):
        report = render_daily_report(self.snapshot, "2026-07-13")

        self.assertIn("无法统计从未创建源码的题目", report)

    def test_rendering_same_snapshot_is_deterministic(self):
        first = render_daily_report(self.snapshot, "2026-07-13")
        second = render_daily_report(self.snapshot, "2026-07-13")

        self.assertEqual(first, second)

    def test_missing_date_raises_clear_error(self):
        with self.assertRaisesRegex(ValueError, "2026-07-14"):
            render_daily_report(self.snapshot, "2026-07-14")


if __name__ == "__main__":
    unittest.main()
