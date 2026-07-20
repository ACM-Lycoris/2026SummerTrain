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

    int n;
    cin>>n;
    vector<int> a(n);

    ll sum1=0,sum2=0;

    for(int i=0;i<n;i++){
        cin>>a[i];
        sum1+=a[i];
        sum2+=(a[i]*a[i]);
    }

    ll ans=n*sum2-sum1*sum1;
    cout<<ans<<endl;

    

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.