#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

int main()
{
    optimize();

    int n, x, y;
    cin >> n >> x >> y;

    vector<int> a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    ll i = 0;
    ll j = 0;
    int minCnt = INT_MAX;
    int cnt0 = 0, cnt1 = 0, cnt2 = 0;

    if (a[0] == 0)
        cnt0++;
    if (a[0] == 1)
        cnt1++;
    if (a[0] == 2)
        cnt2++;

    while (i < n && j < n)
    {

        if (cnt2 < y || cnt1 < x) // a[j]==0绝对不是答案
        {
            j++;
            if (j < n)
            {
                if (a[j] == 0)
                    cnt0++;
                if (a[j] == 1)
                    cnt1++;
                if (a[j] == 2)
                    cnt2++;
            }
            else
            {
                break;
            }
        }

        if (cnt2 >= y && cnt1 >= x) // 恰好相等的时候
        {
            if (cnt0 < minCnt) // 答案可以更新
            {
                minCnt = cnt0; // 更新
            }

            // 收缩左区间
            if (a[i] == 0)
                cnt0--;
            if (a[i] == 1)
                cnt1--;
            if (a[i] == 2)
                cnt2--;

            i++;
        }
    }

    cout << minCnt << endl;

    return 0;
}
