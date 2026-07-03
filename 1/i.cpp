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
    
    int n;
    cin>>n;
    vector<int> num(n,0);
    for(int i=0;i<n;i++){
        cin>>num[i];
    }
    if(n==0)cout<<0;
    if(n==1)cout<<num[0];
    else{
        vector<int> dp(n);
        dp[0]=num[0];
        dp[1]=max(num[0],num[1]);
        for(int i=2;i<n;i++){
            dp[i]=max(dp[i-1],dp[i-2]+num[i]);
        }
        cout<<dp[n-1];
    }
    

    return 0;
}
