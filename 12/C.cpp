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
    ll avg=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        avg+=a[i];
    }
    avg/=n;//平均数
    sort(all(a));
    
    ll sum1=a[0]+a.back();
    sum1/=2;
    cout<<max(1LL,max(abs(sum1-a[0]),abs(sum1-a.back())))<<endl;



    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.