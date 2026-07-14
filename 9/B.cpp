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

    string s;
    cin>>s;
    if(s[0]=='0')cout<<s<<endl;
    else{
        ll len=s.length();
        cout<<1;
        for(ll i=1;i<len;i++){
            if(s[i]=='0')cout<<1;
            else cout<<0;
        }
        cout<<'\n';
    }
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.