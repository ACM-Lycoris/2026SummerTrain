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
    ll k;
    cin >> n >> m >> k;

    vector<ll> A(n + 1, 0), B(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
        A[i] += A[i - 1];
    }

    for (int i = 1; i <= m; i++)
    {
        cin >> B[i];
        B[i] += B[i - 1];
    }

    int i = 0;

    while (i < n && A[i + 1] <= k)
    {
        i++;
    }

    int ans = i;

    for (int j = 1; j <= m; j++)
    {
        while (i > 0 && A[i] + B[j] > k)
        {
            i--;
        }

        if (A[i] + B[j] > k)
        {
            break;
        }

        ans = max(ans, i + j);
    }

    cout << ans << endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.