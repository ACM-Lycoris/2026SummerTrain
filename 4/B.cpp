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

    ll t, n;
    cin >> t >> n;

    while (t--)
    {
        vector<ll> a(n);
        for (ll i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        bool s1 = true, s2 = true, s3 = true, s4 = true;

        if (n > 1 && a[1] < a[0])
        {
            cout << "Sad!\n";
            continue;
        }

        bool ok = true;

        for (int i = 1; i < n; i++)
        {
            if (a[i] == a[i - 1])
            {
                ok = false;
                break;
            }

            if (a[i] > a[i - 1])
            {
                if (!((s1 && s2 && s3 && s4) || (!s1 && !s2 && s3 && s4)))
                {
                    ok = false;
                    break;
                }

                if (i == n - 1)
                {
                    ok = false;
                }
                else
                {
                    if (a[i] > a[i + 1])
                    {
                        if (s2)
                        {
                            s1 = false;
                        }
                        else
                        {
                            s3 = false;
                        }
                    }
                }
            }
            else
            {
                if (!((!s1 && s2 && s3 && s4) || (!s1 && !s2 && !s3 && s4)))
                {
                    ok = false;
                    break;
                }

                if (i == n - 1)
                {
                    s4 = false; // 结束
                }
                else
                {
                    if (a[i] < a[i + 1])
                    {
                        if(s2){
                            s2=false;
                        }
                    }
                }
            }
        }

        if(!s1&&!s2&&!s3&&!s4&&ok){
            cout<<"Havefun!\n";
        }else{
            cout<<"Sad!\n";
        }

    }

    return 0;
}
