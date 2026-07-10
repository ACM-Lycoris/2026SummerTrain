#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;
using ull = unsigned long long;
using lll = __int128;


int main()
{
    optimize();

    ll n;
    cin>>n;
    vector<ll> a(n);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }

    sort(all(a));

    ll ans=0;
    for(int i=0;i<=n;i++){
        //假设有i个老鼠，小于i的恰好有i个
        auto it1=lower_bound(all(a),i)-a.begin();
        auto it2=upper_bound(all(a),i)-a.begin();

        if(it1 == i && it1==it2){
            ans++;
        }

    }
    cout<<ans<<endl;
    
    return 0;
}