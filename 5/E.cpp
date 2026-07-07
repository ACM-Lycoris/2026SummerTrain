#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

const ll p = 1000000007;

ll qpow(ll a, ll b, ll p)
{ // a^b
    a %= p;
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main()
{
    optimize();

    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    sort(all(a));

    vector<ll> fac(200005, 0), InvFac(200005, 0);
    // InvFac[i]=fac[i]^(p-2);

    fac[0] = 1;
    for (ll i = 1; i <= n; i++)
    {
        fac[i] = fac[i - 1] * i % p;
    }
    InvFac[n] = qpow(fac[n], p - 2, p);
    for (ll i = n - 1; i >= 0; i--)
    {
        InvFac[i] = (i + 1) * (InvFac[i + 1]) %p;
    }

    auto C = [&](ll n, ll m) -> ll
    {
        if (n < 0 || m < 0 || m > n)
            return 0;
        return (fac[n]) * (InvFac[m]) % p * (InvFac[n - m]) % p;
    };
    ll PairSum = 0;
    for (ll i = 0; i < n; i++)
    {
        PairSum = ((PairSum % p + p) % p + (a[i] * (2 * i - n + 1) % p + p) % p) % p;
    }

    cout << C(n - 2,k - 2) * PairSum % p << endl;

    return 0;
}