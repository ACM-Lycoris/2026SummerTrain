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

    int n,k;
    cin>>n>>k;
    vector<char> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    vector<pair<char,char>> Bind(k);
    for(int i=0;i<k;i++){
        cin>>Bind[i].first>>Bind[i].second;
    }

    vector<string> ans;
    sort(all(a));//next_permutation前要先sort

    do{
        unordered_map<char,int> mp;
        for(int i=0;i<a.size();i++){
            mp[a[i]]=i;
        }

        bool ok=true;
        for(auto [x1,x2]:Bind){
            //每种约束都遍历一遍
            if(mp[x1]>mp[x2]){
                ok=false;
                break;//只要有一个约束不行
            }
        }
        if(!ok)continue;;//里面不能break;

        string res="";
        for(char c:a){
            res+=c;
        }
        ans.emplace_back(res);
        //cout<<'\n';

    }while(next_permutation(all(a)));

    for(string s:ans){
        cout<<s<<'\n';
    }


    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.