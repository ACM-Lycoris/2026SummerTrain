// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    cin >> T;

    while (T--)
    {
        ll n, m;
        cin >> n >> m;

        vector<string> g(n + 1);
        for (int i = 1; i <= n; i++)
        {
            string s;
            cin >> s;
            g[i] = ' ' + s;
        }

        ll maxKeepRow=n/2-1;
        ll maxKeepCol=m/2-1;

        for (ll i = 1; i <= n / 2; i++)
        {
            for (ll j = 1; j <= m / 2; j++)
            {
                char a = g[i][j];
                char b = g[n - i + 1][j];//下对称
                char c = g[i][m - j + 1];//右对称
                char d = g[n - i + 1][m - j + 1];//右下对称

                if(!(a==b && b==c && c==d)){
                    //一旦不全对称
                    //这个点就要被水池包含

                    maxKeepRow=min(i-1,maxKeepRow);
                    maxKeepCol=min(j-1,maxKeepCol);

                }

            }
        }
        cout<<maxKeepCol*maxKeepRow<<endl;
    }

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.