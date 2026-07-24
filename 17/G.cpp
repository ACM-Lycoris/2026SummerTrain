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

    ll n, m;
    cin >> n >> m;
    vector<ll> Total(n + m);
    vector<ll> driver;
    vector<ll> Common; // 普通居民
    driver.reserve(m);
    Common.reserve(n);

    for (int i = 0; i < m + n; i++)
    {
        cin >> Total[i];
    }

    for (int i = 0; i < m + n; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            driver.emplace_back(Total[i]);
        }
        else
        {
            Common.emplace_back(Total[i]);
        }
    }
    vector<ll> ans(m, 0);
    for (ll num : Common)
    {
        // 对美一位乘客

        int right = upper_bound(all(driver), num) - driver.begin();
        // 第一个大于乘客坐标的
        int left = right - 1; // 小于的

        if (right == 0)
        {
            ans[0]++;
        }
        else if (right == m)
        {
            ans[m - 1]++;
        }
        else
        {
            if (num - driver[left] <=driver[right] - num)
            {
                ans[left]++;
            }
            else
            {
                ans[right]++;
            }
        }
    }

    for (ll a : ans)
    {
        cout << a << ' ';
    }
    cout << endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.