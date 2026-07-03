#include <bits/stdc++.h>
using namespace std;

inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

const ll MOD= 1000000007;

int main()
{
    optimize();
    
    ll n,m;
    cin>>n>>m;

    vector<vector<ll>> dp(n,vector<ll>(m,0));

    for(int i=0;i<m;i++){
        dp[0][i]=1;
    }
    for(int i=0;i<n;i++){
        dp[i][0]=1;
    }

    for(int i =1;i<n;i++){
        for(int j=1;j<m;j++){
            dp[i][j]=(dp[i-1][j]+dp[i][j-1])%MOD;
        }
    }

    cout<<dp[n-1][m-1]<<endl;

    return 0;
}
