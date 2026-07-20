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

    ll n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    if (n == 1)
    {
        cout << 1 << endl;
        return 0;
    }
    else if (n == 2)
    {
        cout << "1 1\n";
        return 0;
    }

    vector<ll> need((n + 1) / 2 + 1);
    for (int i = (n + 1) / 2 - 1; i >= 0; i--)
    {
        int j = n - i - 1;
        need[i] = need[i + 1];
        if (i != j && a[i] != a[j])
        {
            need[i]++;
        }
    }

    int used = 0;

    for (int i = 0; i < (n + 1) / 2; i++)
    {
        int j = n - i - 1;

        for (int x = 1; x <= 26; x++)
        {

            int cost;

            if (i == j)
            {
                cost = (a[i] != x);
            }
            else
            {
                cost = (a[i] != x) + (a[j] != x);
            }

            if (used + cost + need[i + 1] <= 2)
            {
                // 在限度内
                a[i] = x;
                a[j] = x;
                used += cost;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << ' ';
    }
    cout << endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.