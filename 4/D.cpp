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

    int n;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;
        int len = s.length();

        int i = 0;
        int j = len - 1;

        if (s[0] == 'a' && s[j] == 'k')
        {
            cout << "No\n";
            continue;
        }

        bool ok = true;
        while (i < j)
        {
            if (s[i] == s[j])
            {
                i++;
                j--;
                continue;
            }
            else
            {
                if (s[j] == 'a' && j > i + 1)
                {
                    s[j] = 'k';
                    s[j - 1] = 'a';
                    j--;
                    i++;
                }
                else if (s[j] == 'a' && j == i + 1)
                {
                    ok = false;
                    break;
                }
                else if (s[j] == 'k')
                {
                    if (j < len - 1 && i > 1)
                    {
                        if (s[i - 1] == s[j + 1] && s[i - 1] == 'k')
                        {
                            ok = false;
                            break;
                        }
                        else if (s[i - 1] == s[j + 1] && s[i - 1] == 'a')
                        {
                            s[i] = 'k';
                            i++;
                            j--;
                        }
                    }
                }
            }
        }

        cout << (ok ? "Yes" : "No") << endl;
    }

    return 0;
}
