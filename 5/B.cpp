#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

int main()
{
    optimize();

    int T;
    cin>>T;
    while(T--){
        string a,b;
        cin>>a>>b;
        unordered_map<char,char> A,B;unordered_map<char,int> cntA,cntB;
        if(a.length()!=b.length()){
            cout<<"No\n";
        }else{
            int len=a.length();
            bool ok=true;
            for(int i=0;i<len;i++){
                if(cntA[a[i]] == 0){
                    cntA[a[i]]++;
                    A[a[i]]=b[i];
                }else{
                    if(b[i]!=A[a[i]]){
                        //cout<<"No\n";
                        ok=false;
                        break;
                    }
                }
                if(cntB[b[i]] == 0){
                    cntB[b[i]]++;
                    B[b[i]]=a[i];
                }else{
                    if(a[i]!=B[b[i]]){
                        ok=false;
                        break;
                    }
                }
            }
            cout<<(ok?"Yes\n":"No\n");
        }
    }
    
    return 0;
}