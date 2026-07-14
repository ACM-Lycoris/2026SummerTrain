// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

const double pi = 3.1416;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin>>n;

    auto CntFactor = [&](ll num) -> ll{
        ll ans=0;
        for(ll i=1;i*i<=num;i++){
            if(num%i==0){
                if(i*i==num){
                    ans++;
                }else{
                    ans+=2;
                }
            }
        }
        return ans;
    };//统计正因数

    map<ll,ll> mp;//统计奇数次

    while (n--)
    {
        ll x;
        cin>>x;
        mp[x]++;
    }


    for(auto [x,cnt]:mp){
        if(cnt&1){
            //奇数次
            ll Factor=CntFactor(x);
            cout<<x<<' '<<Factor<<'\n';
        }
    }

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.