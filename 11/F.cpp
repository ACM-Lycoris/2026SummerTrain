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

    string A,B;
    cin>>A>>B;

    ll ans=0;
    for(char c1:A){
        for(char c2:B){
            int n1=int(c1-'0');
            int n2=int(c2-'0');
            ans+=(n1*n2);
        }
    }
    cout<<ans<<endl;
    
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.