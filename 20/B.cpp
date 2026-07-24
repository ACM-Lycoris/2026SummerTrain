// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

const ll Log=63;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n,k;
    cin>>n>>k;

    vector<vector<ll>> To(n+1,vector<ll>(Log));
    for(ll i=1;i<=n;i++){
        cin>>To[i][0];
    }


    for(ll j=1;j<Log;j++){
        for(ll i=1;i<=n;i++){
            To[i][j]=To[To[i][j-1]][j-1];
        }
    }

    ll cur=1;

    for(ll j=0;j<Log;j++){
        if((k>>j)&1){
            //如果有点
            cur=To[cur][j];
        }
    }
    cout<<cur<<endl;


    
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.