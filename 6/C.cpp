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

    ll T;
    cin>>T;
    while (T--)
    {   
        
        ll n,m;
        cin>>n>>m;//共有n页m天

        if(2*n%m!=0){
            cout<<0<<endl;
            continue;
        }
        if(m==1){
            cout<<1<<endl;
            continue;
        }
        ll right = 2 * n / m;

        // b 的最大值
        ll maxB = right / (m - 1);

        ll ans = 0;

        if (m % 2 == 1)
        {
            // m 是奇数，m - 1 是偶数
            // (m - 1) * b 永远是偶数
            if (right % 2 == 0)
            {
                ans = maxB + 1;
            }
            else
            {
                ans = 0;
            }
        }
        else
        {
            // m 是偶数，m - 1 是奇数
            // 要求 b 和 right 同奇偶
            if (right % 2 == 0)
            {
                // b = 0, 2, 4, ...
                ans = maxB / 2 + 1;
            }
            else
            {
                // b = 1, 3, 5, ...
                ans = (maxB + 1) / 2;
            }
        }

        cout << ans << '\n';
    
    }
    return 0;
}