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

    ll n;
    cin>>n;
    vector<ll> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(all(a));
    map<ll,ll> Score;//每种数字对应的分数
    ll ans=0;
    
    map<ll,ll,greater<ll>> Id;//分数->索引
    for(int i=0;i<n;i++){
        Score[a[i]]+=a[i];

    }
    for(auto [num,score]:Score){
        Id[score]=num;
    }

    for(auto [score,num]:Id){
        //分数从大到小
        if(Id[Score[num]]==0||score==0){
            continue;
        }
        ans+=score;
        Id[Score[num]]=0;
        if(Id.count(Score[num+1]))Id[Score[num+1]]=0;
        if(Id.count(Score[num-1]))Id[Score[num-1]]=0;

        Score[num]=0;
        if(Score.count(num+1))Score[num+1]=0;
        if(Score.count(num-1))Score[num-1]=0;

    }

    cout<<ans<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.