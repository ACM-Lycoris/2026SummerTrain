// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

const double pi = 3.1416;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin>>n;
    vector<ll> d(n),t(n);

    ll sumD=0;
    ll sumTime=0;
    
    for(ll i=0;i<n;i++){
        cin>>d[i]>>t[i];

        sumD+=d[i]*d[i];
        sumTime+=t[i];

    }

    ll c;cin>>c;

    ll cap = min(c,sumTime);

    vector<ll> dp(cap+1,0);
    for(ll i=0;i<n;i++){
        ll cost = t[i];
        ll val = d[i]*d[i];
        for(ll j=cap;j>=cost;j--){
            dp[j]=max(dp[j],dp[j-cost]+val);
        }
    }

    ll rem = sumD -dp[cap];

    double ans=rem*pi/4.0;
    cout<<fixed<<setprecision(4) << ans<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.