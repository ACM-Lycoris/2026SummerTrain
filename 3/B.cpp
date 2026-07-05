#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll =long long;


int main()
{
    optimize();

    ll n;
    cin>>n;
    ll ans= n*(5*n*n+2*n+1)/4;
    cout<<ans;

    return 0;
}
