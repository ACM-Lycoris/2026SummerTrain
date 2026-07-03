#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}
using ll =long long;

int main()
{
    optimize();

    ll n,m;;
    cin>>n>>m;
    vector<ll> nums(n+2,0);
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }

    vector<ll> suf(n+2,0);
    for(int i=n;i>=1;i--){
        suf[i]=suf[i+1]+nums[i];
    }

    ll Sum=suf[1];
    ll rPos=1;//假设最右侧垃圾点

    for(int i=n;i>=1;i--){
        if(nums[i]>0){
            rPos=i;break;
        }
    }

    auto check=[&](ll Time)-> bool{ //在Time的情况下，清完所有垃圾的人数<=m
        ll Bins= 0; //已清理垃圾树
        ll UsePeople= 0; //派出人数

        ll k=rPos;//

        while(Bins<Sum){
            if(++UsePeople>m)return false;

            ll need=Bins+1;
            while(k>=1&&suf[k]<need)--k;

            ll p = k;
            if(Time<=p)return false;
            Bins+=Time-p;

        }
        return true;

    };

    ll l=0;ll h=rPos+Sum+1;

    while(l<h){
        ll mid=l+(h-l)/2;
        if(check(mid)){
            h=mid;
        }else{
            l=mid+1;
        }
    }
    
    cout<<l<<endl;


    return 0;
}
