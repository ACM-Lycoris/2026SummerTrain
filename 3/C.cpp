#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

const ll MOD= 1e9+7;

int main()
{
    optimize();

    ll n,m;
    cin>>n>>m;

    if(m==1){
        cout<<n<<endl;
        return 0;
    }

    vector<ll> dp(n+1,1);//当前序列结尾是x的序列有多少种,初始各有一种

    ll ans=n%MOD;


    for(ll len=2;len<=m;len++){
        //每种长度算一种答案，
        vector<ll> ndp(n+1,0);
        
        for(ll x=1;x<=n;x++){
            for(ll y=x;y<=n;y+=x){
                ndp[y]+=dp[x];
                ndp[y]%=MOD;
            }
        }

        for(ll num:ndp){
            ans+=num;
            ans%=MOD;
        }
        dp=ndp;
    }   

    cout<<ans<<endl;
    
    return 0;
}
