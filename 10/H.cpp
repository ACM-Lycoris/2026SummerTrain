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

    vector<ll> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    sort(a.begin(),a.end());

    ll sumTime=0;
    ll curWaitTIme=0;
    for(int i=0;i<n;i++){
        sumTime+=curWaitTIme;
        curWaitTIme+=a[i];
    }
    cout<<sumTime<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.