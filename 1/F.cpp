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

    ll n, m, k, l, r;
    cin >> n >> m >> k >> l >> r;
    
    ll ss=n+m+k;
    for(ll i= l;i<=r;i++){
        ll pos=(i-1)%ss;
        if(pos<n)cout<<"W";
        else if(pos<n+m)cout<<"C";
        else{
            cout<<"R";
        }
    }
    //?????
    cout<<endl;

    return 0;
}
