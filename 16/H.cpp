// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x1, x2, x3, y1, y2, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    int ans = max({x1, x2, x3}) - min({x1, x2, x3}) + max({y1, y2, y3}) - min({y1, y2, y3}) + 1;

    cout << ans << endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.