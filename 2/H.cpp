#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll =long long;
const int MOD = 1000000007;
const int MAXN = 2005;

int C[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < MAXN; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }

    int n, m;
    while (cin >> n >> m) {
        int s = n + m;

        ll total = 1LL * C[s][n] * C[s][n] % MOD;
        ll bad = 1LL * C[s][n - 1] * C[s][m - 1] % MOD;

        ll ans = (total - bad + MOD) % MOD;
        cout << ans << '\n';
    }
    
    return 0;
}
