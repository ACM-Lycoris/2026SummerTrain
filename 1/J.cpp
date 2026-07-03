#include <bits/stdc++.h>
using namespace std;

inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}
int n, x, y;

using ll = long long;
int main()
{
    optimize();

    cin >> n >> x >> y;
    x--;
    y--;

    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    if (graph[x][y] == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    else
    {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[x] = 0;
        q.push(x);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            if (u == y)
                break;

            for (int v = 0; v < n; ++v)
            {
                if (graph[u][v] && dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        cout << dist[y] - 1;
    }

    return 0;
}
