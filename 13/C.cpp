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

    ll n, k, m;
    cin >> n >> k >> m;
    vector<ll> time(n);
    for (int i = 0; i < n; i++)
    {
        cin >> time[i];
    }

    ll days = 1;
    ll money = 0;
    ll curDayCost = 0; // 每一天的花费
    for (int i = n - 1; i >= 0; i--)
    {
        if (time[i] > m || days > k)
        {
            break;
        }

        if (curDayCost + time[i] <= m)
        {
            curDayCost += time[i];
            money++;
        }
        else
        {
            curDayCost = 0;
            days++;
            if(days>k){
                break;
            }
            if (curDayCost + time[i] <= m)
            {
                curDayCost += time[i];
                money++;
            }
        }
    }

    cout << money << endl;
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.