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

    int n;
    double m;
    cin >> n >> m;

    vector<double> a(n);
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }

    double save = (sum - m) / n;

    cout << fixed << setprecision(2);

    for (int i = 0; i < n; i++)
    {
        double b = a[i] - save;

        if (fabsl(b) < 0.0005)
            b = 0;
        cout << b <<' ';
    }

    cout << '\n';

    return 0;
}