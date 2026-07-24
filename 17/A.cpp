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
    vector<ll> num(n);
    for(int i=0;i<n;i++){
        cin>>num[i];
    }

    vector<ll> Tree(n+1,0);

    auto add=[&](ll i,ll x)->void{
    
        for(;i<=n;i+=(i&-i)){
            Tree[i]+=x;
        }

    };

    auto query=[&](ll q)->ll{
        ll ans=0;
        ll i=q;
        for(;i;i-=(i&-i)){
            ans+=Tree[i];
        }
        return ans;
    };

    auto kth=[&](ll r,ll k)->ll{ //1到r的第k小
        ll pos=0;ll cnt=0;
        
        ll step=1;
        while((step<<1)<=r){
            step<<=1;
        }
        

    };

    for(int j=1;j<=m;j++){
        //第
        int x;cin>>x;
        //第x人插入后的第j小




    }

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.