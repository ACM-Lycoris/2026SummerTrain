#include <bits/stdc++.h>
using namespace std;

inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

const ll MOD= 1000000007;

int main()
{
    optimize();
    
    int n;
    string s;
    cin>>n>>s;

    for(int k=1;k<=s.length();k++){
        unordered_set<string> sss;
        bool could = true;
        for(int i= 0;i<=s.length()-k;i++){
            string temp=s.substr(i,k);
            if(sss.count(temp)){
                could =false;
                break;
            }
            sss.insert(temp);
        }
        if(could){cout<<k<<endl;
        break;}
    }



    return 0;
}
