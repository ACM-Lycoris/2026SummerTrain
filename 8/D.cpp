// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll l,r;
    cin>>l>>r;

    auto sum=[&](ll num) -> ll{
        ll s=0;
        while(num>0){
            s+=(num%10);
            num/=10;
        }
        return s;
    };

    ll ans=-1;
    ll bestSum=-1;
    for(ll i=l;i<=r;i++){
        if(sum(i)>bestSum || (sum(i)==bestSum && i>ans)){
            ans=i;
            bestSum=sum(i);
        }
    }
    cout<<ans<<endl;
    cout<<bestSum<<endl;
    
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.