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
    vector<pair<ll,ll>> seg(n);
    vector<ll> nums;

    for (ll i = 0; i < n; i++)
    {
        ll x, y;
        cin >> x >> y;

        seg[i] = {x, y};
        nums.push_back(x);
        nums.push_back(y);
    }

    ll q;
    cin >> q;

    vector<ll> query(q);

    for (int i = 0; i < q; i++)
    {
        cin >> query[i];
        nums.push_back(query[i]);

    }
    //  离散
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    ll m = nums.size();
    vector<int> diff(m + 2, 0);

    // 离散下表
    auto getId = [&](ll x)->ll
    {
        return ll(lower_bound(nums.begin(), nums.end(), x) - nums.begin()) + 1;
    };

    for (auto [x, y] : seg)
    {
        ll l = getId(x);
        ll r = getId(y);

        diff[l]++;
        diff[r + 1]--;
    }

    for (int i = 1; i <= m; i++)
    {
        diff[i] += diff[i - 1];
    }
    for (int i = 0; i < q; i++)
    {
        int id = getId(query[i]);

        if (diff[id] > 0)
        {
            cout << "yes ";
        }
        else
        {
            cout << "no ";
        }
    }

    cout << '\n';

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.