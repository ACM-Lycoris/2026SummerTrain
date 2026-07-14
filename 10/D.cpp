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

    ll n,x,y;
    cin>>n>>x>>y;

    ll Before=(x-1)*n - (x-1)*(x-2)/2;
    ll pos = Before +(y-1);

    char ans = char('A'+pos%26);
    cout<<ans<<endl;
    
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.