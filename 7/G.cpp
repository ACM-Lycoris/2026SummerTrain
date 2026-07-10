#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll  = long long;
using ull = unsigned long long;
using lll = __int128;

struct It
{
    int p;
    int a;
    int c;
    int m;
    int g;
};

int main()
{
    optimize();

    int n;
    cin >> n;

    vector<It> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].p >> arr[i].a >> arr[i].c >> arr[i].m >> arr[i].g;
    }

    int P, A, C, M;
    cin >> P >> A >> C >> M;

      // vector<vector<vector<vector<int>>>> dp(P, vector<vector<vector<int>>>(A,vector<vector<int>>(C,vector<int>(M,0))));
      // dp[p][a][c][m];
      // dp[i]=max(dp[i],dp[i-rong]+val);

    auto id = [&](int p, int a, int c, int m)
    {
        return (((p * (A + 1) + a) * (C + 1) + c) * (M + 1) + m);  // 四维压缩成一维编号
    };

    int Total = (P + 1) * (A + 1) * (C + 1) * (M + 1);
    vector<int> dp(Total, 0);

    vector<vector<bool>> take(n, vector<bool>(Total, 0));  // 路径记录数组，take[i][state]表示state下i有没有被选

    for (int i = 0; i < n; i++)
    { // 对每一个小组
        int wp  = arr[i].p;
        int wa  = arr[i].a;
        int wc  = arr[i].c;
        int wm  = arr[i].m;
        int val = arr[i].g;

          // 先取出数据
        for (int p = P; p >= wp; p--)
        {
            for (int a = A; a >= wa; a--)
            {
                for (int c = C; c >= wc; c--)
                {
                    for (int m = M; m >= wm; m--)
                    {

                        int cur = id(p, a, c, m);
                        int pre = id(p - wp, a - wa, c - wc, m - wm);
                        if (dp[pre] + val > dp[cur])
                        {
                            dp[cur]      = dp[pre] + val;
                            take[i][cur] = 1;
                        }
                    }
                }
            }
        }
    }

    vector<int> ans;

    int p = P;
    int a = A;
    int c = C;
    int m = M;

    for (int i = n - 1; i >= 0; i--)
    {
        int cur = id(p, a, c, m);

        if (take[i][cur])
        {
            ans.push_back(i);

            p -= arr[i].p;
            a -= arr[i].a;
            c -= arr[i].c;
            m -= arr[i].m;
        }
    }

    reverse(all(ans));

    cout << ans.size() << endl;
    for (int x : ans)
    {
        cout << x << ' ';
    }

    cout << '\n';
    return 0;
}