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
    
    ll n,x;
    cin>>n>>x;
    vector<pair<int,int>> book(n);

    for(int i=0;i<n;i++){
        cin>>book[i].first;
    }
    for(int i=0;i<n;i++){
        cin>>book[i].second;
    }

    vector<int> dp(x+1,0);
    for(int i=0;i<n;i++){
        for(int j=x;j>=book[i].first;j--){
            dp[j]=max(dp[j],dp[j-book[i].first]+book[i].second);
        }
    }
    cout<<dp[x];

    return 0;
}
