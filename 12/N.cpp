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

    ll n,p2,p3;
    cin>>n>>p2>>p3;

    ll ans = LLONG_MAX;

    for (ll cnt3 = 0; cnt3 <= 20; cnt3++)
    {
        ll remain = max(0LL, n - cnt3 * 3);//剩余人数
        ll cnt2 = (remain + 1) / 2;//上取整两人间

        ans = min(ans, cnt2 * p2 + cnt3 * p3);
    }

    for (ll cnt2 = 0; cnt2 <= 20; cnt2++)
    {
        ll remain = max(0LL, n - cnt2 * 2);
        ll cnt3 = (remain + 2) / 3;

        ans = min(ans, cnt2 * p2 + cnt3 * p3);
    }

    cout << ans << '\n';

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.