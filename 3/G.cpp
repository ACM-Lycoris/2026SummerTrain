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

    ll n, m;
    cin >> n >> m;
    string Old;
    cin >> Old;

    ll len = 1;

    for (int i = 1; i < n; i++)
    {
        if (Old[i] > Old[i % len])
        {
            break;
        }

        if (Old[i] < Old[i % len])
        {
            len = i + 1;
        }
    }

    for (int i = 0; i < m; i++)
    {
        cout << Old[i % len];
    }

    return 0;
}
