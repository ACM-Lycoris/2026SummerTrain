// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

ll maxDelta(const ll &a)
{
    ll Delta = 0;
    string s = to_string(a);
    ll len = s.length();

    if (len == 1)
    {
        return -1 * a;
    }

    for (int i = 0; i < len; i++)
    {
        string cur = "";
        for (int j = 0; j < len; j++)
        {
            if (j != i)
            {
                cur += s[j];
            }
        }
        ll curNum;
        if (cur != "")
        {
            curNum = stoll(cur);
        }
        else
        {
            curNum = 0;
        }

        ll curDelta = (curNum - a);
        if (abs(curDelta) > abs(Delta))
        {
            Delta = curDelta;
        }
    }
    return Delta;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> a(n);
    priority_queue<pair<ll, ll>> pq;
    ll sum = 0;
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
        pq.push({abs(maxDelta(a[i])), i});
    }

    for (ll i = 0; i < n; i++)
    {
        if (!pq.empty())
        {
            auto [delta, id] = pq.top();
            pq.pop();
            ll d    = maxDelta(a[id]);
            a [id] += d;
            sum    += d;
            cout << sum << '\n';
        }
    }

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.