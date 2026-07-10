#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;
using ull = unsigned long long;
using lll = __int128;

int main()
{
    optimize();

    ll a,b,x,y;
    cin>>a>>b>>x>>y;

    ll curBestDiff=LLONG_MAX;

    for(int i=0;i<=x;i++){
        for(int J=0;J<=y;J++){

            ll money= i*a+J*b;

            ll curDiff=abs(money-100);

            curBestDiff=min(curDiff,curBestDiff);

        }
    }

    cout<<curBestDiff<<endl;

    return 0;
}