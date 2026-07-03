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

    ll n;
    cin>>n;
    string s;
    cin>>s;
    ll cntA=0,cntAK=0,cntAKJ=0,cntAKJs=0;
    for(char c:s){
        if(c=='A'){
            cntA += 1;
        } else if (c == 'K') {
            cntAK += cntA;
        } else if (c == 'J') {
            cntAKJ += cntAK;
        } else if (c == 'S') {
            cntAKJs += cntAKJ;
        }
    }

    cout<<cntAKJs<<endl;

    return 0;
}
