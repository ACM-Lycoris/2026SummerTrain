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

        if(s=="ak" || s=="ka" || (len>2 && s[len-1]=='k' && s[0]=='a' )){
            cout<<"No\n";
        }else{
            cout<<"Yes\n";
        }
        
    }

    return 0;
}
