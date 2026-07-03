#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}
using ll =long long;
int main()
{
    optimize();

    int n;
    cin>>n;
    
    vector<ll> Left(n),Right(n);

    for(int i=0;i<n;i++){
        cin>>Left[i]>>Right[i];
    }

    sort(Left.begin(),Left.end());
    sort(Right.begin(),Right.end());

    ll Sum=n;

    for(int i=0;i<n;i++){
        Sum+=max(Left[i],Right[i]);
    }

    cout<<Sum<<endl;

    return 0;
}
