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

    ll n, m;
    cin >> n >> m;

    vector<pair<ll, ll>> students(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> students[i].first >> students[i].second;
    }

    auto check = [&](ll cnt) -> bool
    {
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        pq.push(0);

        ll curCnt = 0;
        for (ll i = 0; i < n; i++)
        {
            if (students[i].first >= pq.top())
            {
                // 到达时间比当前最早结束的时间晚
                // 此人直接上这个机子；
                pq.pop();
                //curCnt++;
                if(curCnt==0){
                    curCnt++;
                }
                pq.push(students[i].first + m);
            }
            else
            {
                // 到达时间内，所有机子都在上机
                if (curCnt < cnt)
                {
                    curCnt++; // 直接新开一个
                    pq.push(students[i].first + m);
                }
                else
                {
                    // cnt内已经满了
                    // 进入等待时间
                    if (students[i].first + students[i].second >= pq.top())
                    {
                        // 能等到
                        ll curTime = pq.top();
                        pq.pop();

                        pq.push(curTime + m);
                    }
                    else
                    { // 不行就爆了
                        return false;
                    }
                }
            }
        }
        return true; // 没有等不及的
    };

    ll l = 1, r = n + 1;

    while (l < r)
    {
        ll mid = l + (r - l) / 2;

        if (check(mid))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }

    cout << l << endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.