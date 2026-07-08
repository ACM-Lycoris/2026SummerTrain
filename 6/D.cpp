#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

int main()
{
    optimize();

    ll n, m;
    cin >> n >> m;

    vector<ll> a(m);
    for (int i = 0; i < m; i++)
    {
        cin >> a[i];
    }

    if (m == 1)
    {
        return 0;
    }
    else if (m == 2)
    {
        cout << abs(a[1] - a[0]) << endl;
    }
    else
    {
        ll Left, Right;
        if (a[1] >= a[0])
        {
            Left  = a[0];
            Right = a[1];
        }
        else
        {
            Left  = a[1];
            Right = a[0];
        }

        for (int i = 1; i < m; i++)
        {
            ll disL = abs(a[i] - Left);
            ll disR = abs(a[i] - Right);

            if(a[i]<Left || a[i] >Right){
                cout << max(disL, disR)<<'\n';
            }else{
                cout<<abs(Right-Left)<<'\n';
            }
            

            Left  = min(a[i], Left);
            Right = max(a[i], Right);
        }
    }

    return 0;
}