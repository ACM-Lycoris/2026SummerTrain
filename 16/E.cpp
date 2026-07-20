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
    map<pair<int, int>, int> mp; // 判断某个坐标是否有点
    vector<pair<int, int>> wheelsPos(n);
    // vector<int> X(n), Y(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        wheelsPos[i].first = x;
        wheelsPos[i].second = y;
        mp[{x, y}]++;
        //  X[i] = x;
        // Y[i] = y;
    }

    // sort(all(X));
    // sort(all(Y));

    // X.erase(unique(all(X)), X.end());
    // Y.erase(unique(all(Y)), Y.end());

    // for(int i=0;i<n;i++){

    // }

    int cnt = 0;

    for (auto [x1, y1] : wheelsPos)
    {
        for (auto [x3, y3] : wheelsPos)
        {

            if (x1 == x3 && y1 == y3)
            {
                continue;
            }

            int x2 = (x1 + y1 + x3 - y3);
            if (x2 & 1)
            {
                continue;
            }
            else
            {
                x2 >>= 1;
            }
            int y2 = x3 + y3 + y1 - x1;
            if (y2 & 1)
            {
                continue;
            }
            else
            {
                y2 >>= 1;
            }
            int x4 = x1 - y1 + x3 + y3;
            if (x4 & 1)
            {
                continue;
            }
            else
            {
                x4 >>= 1;
            }
            int y4 = y1 + x1 + y3 - x3;
            if (y4 & 1)
            {
                continue;
            }
            else
            {
                y4 >>= 1;
            }

            if (mp.count({x2, y2}) && mp.count({x4, y4}))
            {
                cnt++;
            }
        }
    }

    cout << cnt/4 << endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.