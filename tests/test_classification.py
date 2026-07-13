import unittest

from analyzer.classification import classify_algorithms


def tags(source: str) -> dict[str, list[str]]:
    return {item["tag"]: item["evidence"] for item in classify_algorithms(source)}


class ClassificationTests(unittest.TestCase):
    def test_detects_dynamic_programming(self):
        result = tags("vector<int> dp(n); dp[i]=max(dp[i-1],dp[i-2]+a[i]);")
        self.assertIn("DP", result)
        self.assertTrue(result["DP"])

    def test_detects_graph_traversal_and_dsu(self):
        bfs = tags("queue<int> q; q.push(1); while(!q.empty()){ q.pop(); }")
        dsu = tags("int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}")
        self.assertIn("图论", bfs)
        self.assertIn("数据结构", bfs)
        self.assertIn("图论", dsu)

    def test_detects_greedy_priority_queue(self):
        result = tags("sort(a.begin(),a.end()); priority_queue<int> pq; pq.push(a[0]);")
        self.assertIn("贪心", result)
        self.assertIn("数据结构", result)

    def test_detects_binary_search_with_check(self):
        source = "while(l<r){int mid=l+(r-l)/2;if(check(mid))r=mid;else l=mid+1;}"
        self.assertIn("二分", tags(source))

    def test_detects_math_string_and_geometry(self):
        math = tags("long long qpow(long long a,int b){return a*b%MOD;}")
        string = tags("string s; vector<int> prefix_function(s.size());")
        geometry = tags("long long cross(Point a, Point b); double area = dx * dy / 2.0;")
        self.assertIn("数学", math)
        self.assertIn("字符串", string)
        self.assertIn("几何", geometry)

    def test_unrelated_program_is_unclassified(self):
        self.assertEqual(classify_algorithms("int main(){return 0;}"), [{"tag": "未分类", "evidence": []}])


if __name__ == "__main__":
    unittest.main()
