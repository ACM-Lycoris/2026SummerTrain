// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

const ll MOD = 1e9+7;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n,k;
    cin>>n>>k;
    
    ll p=1;
    while(p<n){
        p*=2;
    }
    if(p>=n){
        p/=2;
    }

    ll cnt=0;
    __int128 sumLeft=0,sumRight=0;
    //p是最终截断位置
    while(k--){
        ll x,y;
        cin>>x>>y;
        
        if(cnt+x<=p){
            sumLeft=(sumLeft+((__int128)x*y)%MOD)%MOD;
            cnt+=x;
        }else{
            if(cnt<p){
                __int128 curLeft=(__int128)(p-cnt)*y%MOD;
                sumLeft=(sumLeft+curLeft)%MOD;
                __int128 curRight=(cnt+x-p)*(__int128)y%MOD;
                sumRight=(sumRight+curRight)%MOD;
            }//卡在边的情况
            else{//已经超过边界的情况
                sumRight=(sumRight+((__int128)x*y)%MOD)%MOD;
            }
            cnt+=x;
        }
    }

    ll ans = ((sumLeft%MOD)*(sumLeft%MOD)+(sumRight%MOD)*(sumRight%MOD))%MOD;

    cout<<ans<<endl;
    
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.