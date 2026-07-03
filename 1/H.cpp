#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

bool checkNum(string s,int maxVal){

    if(s.empty())return false;
    if(s.length()>5)return false;
    if(s.length()>1 && s[0] == '0')return false;

    for(char c:s){
        if(!isdigit(c))return false;
    }
    return stoi(s)<=maxVal;

}

bool check(string s){

    vector<string>parts;
    string sep="";
    string cur="";

    for(char c:s){
        if(c=='.'||c==':'){
            sep+=c;
            parts.emplace_back(cur);
            cur.clear();
        }else{
            if(isdigit(c)){
                cur+=c;
            }else{
                return false;
            }
        }
    }
    parts.emplace_back(cur);
    if(sep!="...:"){
        return false;
    }
    for (int i = 0; i < 4; i++)
        if (!checkNum(parts[i], 255)) return false;
    return checkNum(parts[4], 65535);
}

int main()
{
    optimize();

    ll n;
    cin>>n;

    unordered_set<string> ser;
    unordered_map<string,int>serID;

    for(int i=0;i<n;i++){
        string op,ad;
        cin>>op>>ad;
        if(op=="Server"){
            if(check(ad)){
                if(!ser.count(ad)){
                    ser.insert(ad);
                    serID[ad]=i+1;
                    cout<<"OK\n";
                }else{
                    cout<<"FAIL\n";
                }
            }else{
                cout<<"ERR\n";
            }
        }else{
            //Client
            if(!check(ad)){
                cout<<"ERR\n";
            }else{
                if(ser.count(ad)){
                    cout<<serID[ad]<<"\n";
                }else{
                    cout<<"FAIL\n";
                }
            }
        }
    }

    return 0;
}