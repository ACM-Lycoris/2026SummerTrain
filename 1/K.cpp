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

    int n;
    cin>>n;

    vector<string> words1(n),words2(n);
    for(int i=0;i<n;i++){
        cin>>words1[i]>>words2[i];
    }

    vector<int> Alphas(26,0);

    for(int i=0;i<26;i++){
        char c= char('a'+i);
        ll curCnt=0;
        for(int j=0;j<n;j++){

            ll Cnt1=0,Cnt2=0;
            for(char cc:words1[j]){
                if(cc==c) Cnt1++;
            }
            for(char cc:words2[j]){
                if(cc==c) Cnt2++;
            }

            curCnt+=max(Cnt1,Cnt2);
        }

        Alphas[i]=curCnt;
    }

    for(int num:Alphas){
        cout<<num<<endl;
    }

    return 0;
}