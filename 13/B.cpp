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

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    map<ll, int> cnt;map<ll, int> last;

    set<tuple<int, int, ll>> ranking;

    ll lucky = 1; //第一天固定选1
    //应该是吧
    int answer = 0;

    for (int day = 1; day <= n; day++)
    {
        bool win = (lucky == a[day]);


        if (win)
        {
            answer++;
        }

        
        ll x = a[day];

        if (cnt.count(x))
        {
            ranking.erase({cnt[x], last[x], x});
        }

        cnt[x]++;
        last[x] = day;

        ranking.insert({cnt[x], last[x], x});

        if (day < n && !win)
        {
            lucky = get<2>(*ranking.rbegin());//


        }



    }

    cout<<answer<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.