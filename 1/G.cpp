#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

int main()
{
    optimize();

    ll n,k;
    cin>>n>>k;
    
    vector<ll> Times(n);
    for(int i=0;i<n;i++){
        cin>>Times[i];;
    }
    sort(Times.begin(),Times.end());

    ll allTime =  Times.back()-Times[0]+1;

    vector<pair<ll,ll>> Gaps(n-1);
    for(int i=0;i<n-1;i++){
        Gaps[i].first  = Times[i+1]-1-Times[i];
        Gaps[i].second = i;
    }

    sort(Gaps.begin(),Gaps.end(),[&](const pair<ll,ll> &a,const pair<ll,ll> &b){
        return a.first>b.first;//sort with gap's Length
    });

    for(int i=0;i<k-1;i++){
        allTime-=Gaps[i].first;
    }

    cout<<allTime;
    return 0;
}
