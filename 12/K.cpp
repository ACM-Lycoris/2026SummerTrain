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

    ll c,n;
    cin>>c>>n;

    if(n/c==0 ){
        cout<<-1<<endl;
        return 0;
    }

    if(n/c==1){
        cout<<c*c<<endl;
        return 0;
    }
    
    ll cnt=n/c;
    cout<<(cnt*c*((cnt-1)*c))<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.