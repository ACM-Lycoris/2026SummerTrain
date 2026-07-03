#include <bits/stdc++.h>
using namespace std;

inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}
int n, m;

int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int dy[] = {1, 1, 1, 0, -1, -1, -1, 0};

void DFS(vector<vector<char>> &grid, int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] != 'W')
        return;

    grid[x][y] = '.';

    for (int k = 0; k < 8; k++)
    {
        int nx = x + dx[k];
        int ny = y + dy[k];
        DFS(grid, nx, ny);
    }
}

int main()
{
    optimize();

    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m, '0'));
    for (int i = 0; i < n; i++)
    {
        string line;
        cin >> line;
        for (int j = 0; j < m; j++)
        {
            grid[i][j] = line[j];
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'W')
            {
                cnt++;
                DFS(grid, i, j);
            }
        }
    }

    cout << cnt << endl;

    return 0;
}