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

    ll n;
    cin>>n;

    static ll f[35][35];//auto 0
    for(int b=1;b<=n;b++){
        f[0][b]=1;
    }

    for(int a=1;a<=n;a++){
        for(int b=1;b<=n;b++){
            f[a][b]=f[a-1][b]+f[a][b-1];
        }
    }
    cout<<f[n][n]<<endl;

    return 0;
}