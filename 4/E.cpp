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

    ll T;
    cin >> T;
    while (T--)
    {
        string s;
        cin >> s;
        ll len = s.length();
        ll ans = 0;

        ll i = 0, j = len - 1;

        ll Left1 = 0, Right1 = 0;

        bool ok = false;

        while (i < j)
        {
            if (s[i] == s[j])
            {
                if (s[i] == '0')
                {
                    Left1  = 0;
                    Right1 = 0;
                }
                else
                {
                    Left1++;
                    Right1++;
                }
                i++;
                j--;
            }
            else
            {

                if (s[i] == '1')
                {
                    Left1++;
                }
                else
                {
                    Right1++;
                }

                if (s[i] == '0')
                {
                      // 左为0插入左边1

                    ans    += (Right1 - Left1);
                    
                    Right1 -= Left1;
                    Left1   = Right1;
                    j--;
                }
                else if (s[i] == '1')
                {
                      // 右为0右边插入1
                    ans    += (Left1 - Right1);
                    Left1  -= (Right1);
                    Right1  = Left1;
                    i++;
                }
            }
        }

        cout << ans << endl;
    }

    return 0;
}
