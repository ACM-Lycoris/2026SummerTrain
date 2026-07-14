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

    ll n;
    cin >> n;
    vector<pair<ll, ll>> Site(n);
    map<pair<ll, ll>, ll> mp;
    for (ll i = 0; i < n; i++)
    {
        cin >> Site[i].first >> Site[i].second;
        mp[{Site[i].first, Site[i].second}]++; // 代表存在
    }

    ll maxArea = 0;

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            auto [AX, AY] = Site[i];
            auto [BX, BY] = Site[j];

            if (i == j)
            {
                continue; // 不判定同样点
            }

            if ((AX + BX + AY - BY) % 2 != 0 || (AY + BY + BX - AX) % 2 != 0 
             || (AX + BX - AY + BY) % 2 != 0 || (AY + BY - BX + AX) % 2 != 0)
            {
                continue;
            }

            ll CX = (AX + BX + AY - BY) / 2;
            ll CY = (AY + BY + BX - AX) / 2;

            ll DX = (AX + BX - AY + BY) / 2;
            ll DY = (AY + BY - BX + AX) / 2;

            if (mp.count({CX, CY}) && mp.count({DX, DY}))
            {
                ll dx = abs(BX - AX);
                ll dy = abs(BY - AY);
                ll curArea = (dx * dx + dy * dy) / 2; // 对角线长度除以根2，的平方

                maxArea = max(maxArea, curArea);
            }
        }
    }

    cout << maxArea << endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.