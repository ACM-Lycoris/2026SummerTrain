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

    int T;
    cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        vector<bool> possible(n + 1, false);

        for (int i = 0; i < n; i++)
        {
            if (i + 1 < n && a[i] == a[i + 1])
            {
                possible[a[i]] = true;
            }
            if (i + 2 < n && a[i] == a[i + 2])
            {
                possible[a[i]] = true;
            }
        }

        bool Could = false;

        for (int i= 1; i <= n; i++)
        {
            if (possible[i])
            {
                cout<<i<<' ';
                Could = true;
            }
        }

        if (!Could)
        {
            cout << -1;
        }

        cout<<endl;
    }

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.