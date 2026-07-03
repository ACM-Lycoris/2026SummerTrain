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
    
    int d;
    string s;
    cin>>d>>s;

    int keep=s.length()-d;
    stack<char> stk;

    for(char c:s){
        while(!stk.empty() && stk.top()<c && d >0){
            stk.pop();
            d--;//used one count
        }
        //if not,push this one into stack
        stk.push(c);
    }

    while(d>0){//
        stk.pop();
        d--;
    }

    string res="";
    while(!stk.empty()){
        res+=stk.top();
        stk.pop();
    }

    reverse(res.begin(),res.end());
    cout<<res<<endl;






    return 0;
}
