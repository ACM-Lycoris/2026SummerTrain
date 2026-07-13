import unittest

from analyzer.quality import analyze_quality


def by_rule(source: str) -> dict[str, dict]:
    return {finding["rule_id"]: finding for finding in analyze_quality(source, "1/A.cpp")}


class QualityTests(unittest.TestCase):
    def test_flags_constant_subscript_boundary_risk(self):
        result = by_rule("vector<int> a(n);\nint x = a[1];\n")
        self.assertEqual(result["CPP001_FIXED_SUBSCRIPT"]["line"], 2)
        self.assertIn("可能", result["CPP001_FIXED_SUBSCRIPT"]["message"])

    def test_flags_map_subscript_in_condition_but_not_count(self):
        risky = by_rule("map<int,int> mp;\nif (mp[key]) use();\n")
        clean = by_rule("map<int,int> mp;\nif (mp.count(key)) use();\n")
        self.assertEqual(risky["CPP002_MAP_IMPLICIT_INSERT"]["line"], 2)
        self.assertNotIn("CPP002_MAP_IMPLICIT_INSERT", clean)

    def test_flags_nested_input_sized_loops(self):
        source = "for(int i=0;i<n;i++){\n  for(int j=0;j<m;j++){ work(); }\n}\n"
        result = by_rule(source)
        self.assertEqual(result["CPP003_NESTED_LOOP"]["line"], 2)

    def test_does_not_flag_sequential_loops_as_nested(self):
        source = (
            "for(int i=0;i<n;i++){ read(a[i]); }\n"
            "for(int i=0;i<n;i++){ sum += a[i]; }\n"
        )

        self.assertNotIn("CPP003_NESTED_LOOP", by_rule(source))

    def test_flags_recursive_dfs(self):
        source = "void DFS(int x){\n if(x) DFS(x-1);\n}\n"
        self.assertEqual(by_rule(source)["CPP004_RECURSIVE_DFS"]["line"], 2)

    def test_flags_low_precision_pi(self):
        source = "const double pi = 3.1416;\n"
        self.assertEqual(by_rule(source)["CPP005_PI_PRECISION"]["line"], 1)

    def test_flags_runtime_sized_dp(self):
        source = "long long cap; cin>>cap;\nvector<long long> dp(cap+1, 0);\n"
        self.assertEqual(by_rule(source)["CPP006_RUNTIME_DP"]["line"], 2)

    def test_clean_simple_program_has_no_findings(self):
        source = "int main(){ long long n=0; cin>>n; cout<<n+1; }\n"
        self.assertEqual(analyze_quality(source, "1/A.cpp"), [])


if __name__ == "__main__":
    unittest.main()
