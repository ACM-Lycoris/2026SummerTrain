#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

int main()
{
    optimize();

    int n,m;
    cin>>n>>m;

    string s;
    cin>>s;
    s=s+s;
    int L=s.length();
    int pos1,pos2;
    for(int i=m;i<L;i++){
        if(s[i]=='B'){

            pos1=i-(m-1);
            break;
        }
    }

    cout<<pos1;

    return 0;
}
