#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;
using ull = unsigned long long;
using lll = __int128;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
//vector<vector<int>> graph;
//vector<vector<bool>> vis;

// void DFS(int x, int y, int &step)
// {
//     if (x < 0 || y < 0 || x >= graph.size() || y >= graph[0].size() || vis[x][y])
//         return;
// }

int main()
{
    optimize();

    int n;
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }
    ll step = 0; //! NewStep & graph[i][j]的时候才能走

    if (n == 1)
    {
        cout << 1 << endl;
        return 0;
    }
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(n, vector<int>(2, -1)));
    queue<tuple<int, int, int>> q;

    dist[0][0][0] = 0; // dist[i][j][X]表示到ij位置处且当前时间奇偶性为X的最短时间
    q.push({0, 0, 0});

    while (!q.empty())
    {
        auto [x, y, t] = q.front();
        q.pop();

        if (x == n - 1 && y == n - 1)
        {
            cout << t << '\n';
            return 0;
        }

        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];
            int nt = t + 1;
            int p = nt % 2;//奇偶性

            if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                continue;

            if (graph[nx][ny] != p)
                continue;

            if (dist[nx][ny][p] != -1)
                continue;

            dist[nx][ny][p] = nt;
            q.push({nx, ny, nt});
        }
    }

    return 0;
}