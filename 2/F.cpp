#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll =long long;

const ll K  = 2048;

int main()
{
    optimize();

    ll n,m;
    cin>>n>>m;
    vector<ll> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    vector<ll> dp(K,INT_MAX);//dp[i]表示前缀异或值为i时的最少操作次数
    //这里不能开到K+1,因为第2048个位置是不合法的
    dp[0]=0;

    for(int i=0;i<m;i++){
        //对前m个数字中的某一个的组,也就是a[i]对应的同余组
        vector<ll> nums;//出现了哪些数字
        vector<ll> cnts(K+1,0);//每个数字出现了几次
        ll totalNum=0;//这个组里面有多少个数字

        for(int j=i;j<n;j+=m){
            if(cnts[a[j]]==0){
                nums.emplace_back(a[j]);
            }
            cnts[a[j]]++;
            totalNum++;
        }

        ll minOld=*min_element(dp.begin(),dp.end());

        vector<ll> ndp(K,minOld+totalNum);

        for(ll x:nums){
            ll cost = totalNum-cnts[x];

            for(ll pre=0;pre<K;pre++){
                //pre表示前面选出来的异或和，当前选x，那新的异或和就是pre^x
                ll newTo=pre^x;
                ndp[newTo]=min(ndp[newTo],dp[pre]+cost);
            }

        }
        dp=ndp;
    }

    cout<<dp[0]<<'\n';
    
    return 0;
}
