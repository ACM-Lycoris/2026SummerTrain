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

    int n, m;
    cin >> n >> m;

    vector<vector<char>> g(n + 1, vector<char>(m + 1, ' '));

    for (int i = 1; i <= n; i++)
    {
        string line;
        cin >> line;
        line = ' ' + line;
        for (int j = 1; j <= m; j++)
        {
            g[i][j] = line[j];
        }
    }

    vector<vector<int>> H(n + 1, vector<int>(m + 1, 0)); // 横向二维前缀和
    vector<vector<int>> V(n + 1, vector<int>(m + 1, 0)); // 纵向二位前缀和

    // 先维护横向
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j == m)
            {
                H[i][j] == H[i][j - 1];
            } // 边界
            else
            {
                if (g[i][j] == '.' && g[i][j + 1] == '.')
                {
                    H[i][j]++;
                }
                H[i][j] = H[i][j] + H[i - 1][j] + H[i][j - 1] - H[i - 1][j - 1];
            }
        }
    }

    // 纵向
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i == n)
            {
                H[i][j] == H[i - 1][j];
            } // 边界
            else
            {
                if (g[i][j] == '.' && g[i + 1][j] == '.')
                {
                    V[i][j]++;
                }
                V[i][j] = V[i][j] + V[i - 1][j] + V[i][j - 1] - V[i - 1][j - 1];
            }
        }
    }

    auto Query = [&](ll r1, ll c1, ll r2, ll c2) -> ll
    {
        ll Crosswise  = H[r2][c2 - 1] //横向木棍
        - H[r2][c1 - 1] 
        - H[r1 - 1][c2 - 1] 
        + H[r1 - 1][c1 - 1];

        ll Lengthways = V[r2 - 1][c2] //纵向木棍
        - V[r2 - 1][c1 - 1] 
        - V[r1 - 1][c2] 
        + V[r1 - 1][c1 - 1];

        ll queryResult=Crosswise+Lengthways;
        return queryResult;

    };

    ll q;
    cin >> q;
    while (q--)
    {
        ll r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        cout<<Query(r1,c1,r2,c2)<<'\n';

    }

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.