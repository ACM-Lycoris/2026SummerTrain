#include <bits/stdc++.h>
using namespace std;

inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

const ll MOD = 1000000007;

int main()
{
    optimize();

    ll q,k;
    cin>>q>>k;
    //对于某状态
    vector<ll> dpPref(114514,0);//dp前缀和
    
    vector<ll> dpW(114514,0);//dp[i]为走路结尾
    vector<ll> dpR(114514,0);//dp[i]为跑步结尾
    dpW[0]=1;dpW[1]=1;
    for(int i=1;i<=114513;i++){
        dpW[i]=(dpW[i-1]+dpR[i-1])%MOD;
        if(i>=k){
            dpR[i]=dpW[i-k];
        }
    }
    for(int i=1;i<=114513;i++){
        dpPref[i]=((dpW[i]+dpR[i])%MOD+dpPref[i-1])%MOD;
    }
    
    while(q--){
        ll l,r;
        cin>>l>>r;
        cout<<((dpPref[r]-dpPref[l-1])%MOD+MOD)%MOD<<'\n';
    }
    
    return 0;
}