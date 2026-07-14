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

    ll M,T,U,F,D;
    cin>>M>>T>>U>>F>>D;

    ll Time=0;
    ll ans =0;
    for(ll i=1;i<=T;i++){
        char s;
        cin>>s;
        ll cost=0;
        if(s=='u'){
            cost+=(U+D);
        }else if(s=='d'){
            cost+=(D+U);
        }else {
            cost+=2*F;
        }
        if(Time+cost > M){
            break;
        }


        Time+=cost;
        ans++;

    }
    cout<<ans<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.