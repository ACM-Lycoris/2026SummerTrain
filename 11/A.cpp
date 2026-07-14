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

    ll n, m; // n人m个羊腿
    cin>>n>>m;
    

    vector<ll> Appetite(n), Gigot(m);
    for (int i = 0; i < n; i++)
    {
        cin >> Appetite[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> Gigot[i];
    }
    sort(all(Appetite));

    ll ans = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    // 堆的大小就是当前已经被分配的腿
    for (int i = 0; i < n; i++)
    {

        // 对于当前人A[i];
        if (pq.size() < Appetite[i])
        {
            // 当前堆里能融入
            pq.push(Gigot[Appetite[i] - 1]);
        }
        else
        {
            if (!pq.empty())
            {
                ll curMin = pq.top();
                ans += curMin;
                pq.pop();
                pq.push(Gigot[Appetite[i] - 1]);
            }
        }
    }
    cout << ans << endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.