// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

string removeZero(string &s){
    bool start=false;
    string res="";
    for(char c:s){
        if(c=='0' && start==0){
            continue;
        }
        if(c!='0'){
            start = 1;
        }
        if(start){
            res+=c;
        }
    }

    if(!start){
        return "0";
    }else{
        return res;
    }

}

ll getAns(const string &s){//前一步去除前导0，这一步直接开始
    //长除法

    ll remainder=0;

    for(char c:s){
        ll digit=c-'0';
        remainder=(remainder*10 +digit)%7;
    }
    return remainder;
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin>>s;
    s=removeZero(s);
    cout<<getAns(s)<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.