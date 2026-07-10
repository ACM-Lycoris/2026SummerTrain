// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin>>s;

    int jx=0,jl=0,js=0;


    for(char c:s){
        if(c=='x'){
            jx++;
        }
        if(c=='l' && jx>0){
            jx--;
            jl++;
        }
        if(c=='s' && jl>0){
            jl--;
            js++;
        }
    }
    cout<<js<<endl;
    
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.