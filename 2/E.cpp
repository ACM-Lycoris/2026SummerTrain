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

    ll n;
    cin>>n;
    vector<ll> nums(n);

    ll maxA=-1;
    for(int i=0;i<n;i++){
        cin>>nums[i];
        maxA=max(maxA,nums[i]);
    }

    vector<ll> cnt(maxA+1,0);
    vector<ll> sum(maxA+1,0);

    //对每个数字处理
    for(ll num:nums){
        vector<pair<ll,ll>> arr;//比这一个数字小的数字和其对应代价
        ll x=num;//取出备用
        ll downCost=0;

        while(x>0){
            ll y=x;
            ll upCost=0;

            while(y<=maxA){
                //y*2还没有到最大值的时候
                arr.emplace_back(y,upCost+downCost);
                y*=2;
                upCost++;
            }

            x/=2;
            downCost++;

        }//枚举所有的x/2,对每个x/2都*2枚举到maxA;
        
        sort(arr.begin(),arr.end());

        for(int i=0;i<arr.size();){
            ll tar=arr[i].first;
            ll bestCost=arr[i].second;

            ll j=i+1;
            while (j<arr.size()&& arr[j].first==tar)
            {
                j++;
            }

            cnt[tar]++;
            sum[tar]+=bestCost;

            i=j;
        }
    }

    ll ans=LLONG_MAX;

    for(ll i = 0 ;i<maxA+1 ;i++){
        if(cnt[i]==n){
            ans=min(ans,sum[i]);
        }
    }

    cout<<ans<<endl;
    
    
    return 0;
}
