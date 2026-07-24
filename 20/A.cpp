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

    ll n;
    cin>>n;
    vector<ll> a(n);
    for(ll i=0;i<n;i++){
        cin>>a[i];
    }

    ll x1=a[0];;

    for(int i=1;i<n-1;i++){
        if(i&1){
            x1-=a[i];
        }else{
            x1+=a[i];
        }
    }

    x1=(x1+a[n-1])/2;
    vector<ll> res;
    res.emplace_back(x1);
    ll lastX=x1;
    for(int i=0;i<n-1;i++){
        ll nextX=a[i]-lastX;
        res.emplace_back(nextX);
        
        lastX=nextX;

    }

    for(ll x:res){
        cout<<2*x<<' ';
    }

    cout<<endl;
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.