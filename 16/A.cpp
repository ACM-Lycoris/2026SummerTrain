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

    ll n, m, t;
    cin >> n >> m >> t;
    vector<vector<pair<ll, ll>>> graph(n+1);

    map<pair<ll, ll>, int> isRepeat;

    for (int i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        if (!isRepeat.count({u, v}))
        {
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
            isRepeat[{u, v}] = w;
            isRepeat[{v, u}] = w;
        }
        else
        {
            // 重复边应存下最小值
            if (isRepeat[{u, v}] <= w)
            {
                continue;
            }
            else
            {
                isRepeat[{u, v}] = w;
                isRepeat[{v, u}] = w;
            }
        }
    }

    vector<ll> dist(n + 1, INT_MAX);

    auto Dijkstra = [&]() -> ll
    {
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[0] = 0;
        pq.push({0, 0});

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u])
                continue;
            if (u == t)
                return d; // 提前终止

            for (auto [v, w] : graph[u])
            {
                if (dist[v] > d + w)
                {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist[t] == INT_MAX ? -1 : dist[t];
    };

    ll ans=Dijkstra();
    cout<<ans<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.