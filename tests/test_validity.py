import unittest

from analyzer.validity import analyze_source


class ValidityTests(unittest.TestCase):
    def test_empty_source_is_attempted(self):
        result = analyze_source("\n// comment\n")

        self.assertFalse(result["valid_code"])
        self.assertEqual(result["validity_reason"], "empty")
        self.assertEqual(result["line_count"], 2)
        self.assertEqual(result["code_line_count"], 0)

    def test_missing_main_is_attempted(self):
        result = analyze_source("int solve() { return 42; }\n")

        self.assertFalse(result["valid_code"])
        self.assertEqual(result["validity_reason"], "missing_main")

    def test_template_only_main_is_attempted(self):
        source = """#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
"""

        result = analyze_source(source)

        self.assertFalse(result["valid_code"])
        self.assertEqual(result["validity_reason"], "template_only")

    def test_solution_with_input_and_output_is_valid(self):
        source = "int main(){int n; std::cin>>n; std::cout<<n+1; return 0;}"

        result = analyze_source(source)

        self.assertTrue(result["valid_code"])
        self.assertEqual(result["validity_reason"], "substantive")

    def test_comments_and_strings_do_not_break_structure_detection(self):
        source = 'int main(){/* } */ std::cout << "}"; return 0;}'

        self.assertTrue(analyze_source(source)["valid_code"])


if __name__ == "__main__":
    unittest.main()
