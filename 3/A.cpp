#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll =long long;


int main()
{
    optimize();

    ll n;
    cin>>n;
    vector<tuple<ll,ll,ll>> arr(n);
    ll maxAns=0,maxI=0;

    for(int i=0;i<n;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        get<0>(arr[i])=a;
        get<1>(arr[i])=b;
        get<2>(arr[i])=c;
        ll curANs=c/b*a;
        if(curANs>maxAns){
            maxAns=curANs;
            maxI=i+1;
        }
    } 

    cout<<maxI;



    return 0;
}
