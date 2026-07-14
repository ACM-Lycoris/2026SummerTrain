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

    ll n,m;
    cin>>n>>m;
    vector<ll> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(all(a));
    vector<ll> Diffs;
    for(ll i=1;i<n;i++){
        ll curDiff=(a[i]-a[i-1]);
        Diffs.emplace_back(curDiff);
    }
    sort(all(Diffs));
    ll ans=0;
    for(ll i=0;i<n-m;i++){
        ans+=Diffs[i];
    }

    cout<<ans<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.