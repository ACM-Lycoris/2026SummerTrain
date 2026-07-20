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


    string s;
    cin>>s;
    int n=s.length();
    for(char &c:s){
        if(islower(c)){
            c=toupper(c);
        }
    } 
    s=' '+s;
    string text=" NHOI";
    vector<int> Next(5,0);
  //  cout<<s<<endl;

    ll cnt=0;
    for(int i=1,j=0;i<=n;i++){
        while(j && s[i]!=text[j+1]){
            j=Next[j];
        }
        if(s[i]==text[j+1]){
            j++;
        }
        if(j==4){
            cnt++;
            j=Next[j];
        }
    }
    cout<<cnt<<endl;


    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.