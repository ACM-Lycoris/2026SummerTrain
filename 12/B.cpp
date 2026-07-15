// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> degree(n + 1, 0);
    int maxD = -1;

    int _ = n - 1;
    for (int i = 0; i < _; i++)
    { // 数据范围标记

        int x, y;
        cin >> x >> y;
        degree[x]++;
        degree[y]++;

        maxD = max({degree[x], degree[y], maxD});
    }

    cout << maxD + 1 << endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.