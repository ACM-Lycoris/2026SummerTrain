#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

int n;
const int MAXN = 400005;

int a[MAXN], b[MAXN];
int fa[MAXN];
int dist[MAXN];

int Find(int x)
{

    if (fa[x] == x)
        return x;
    return fa[x] = Find(fa[x]);
}

int main()
{
    optimize();

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }

    for (int i = 1; i <= n + 1; i++)
    {
        fa[i] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        dist[i] = -1;
    }

    queue<int> q;
    dist[n] = 0;
    q.push(n);

    int ans = -1;
    while (!q.empty())
    {

        int x = q.front();
        q.pop();

        int L = x - a[x];
        int R = x;

        if (L <= 0)
        {
            ans = dist[x] + 1;
            break;
        }

        L = max(1, L);

        for (int j = Find(L); j <= R; j = Find(j))
        {
            int cur = j;
            fa[cur] = Find(cur + 1);
            int to = cur + b[cur];

            if (to >= 1 && to <= n && dist[to] == -1)
            {
                dist[to] = dist[x] + 1;
                q.push(to);
            }
        }
    }

    cout << ans << endl;

    return 0;
}
