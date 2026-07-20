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

    ll n,m ,k,K;
    cin>>n>>m>>k>>K;

    vector<ll> val(n);
    ll sum=0;
    for(int i=0;i<n;i++){
        cin>>val[i];
        sum+=val[i];
    }

    sort(all(val));

    if(sum>m){
        cout<<"Impossible\n";
        return 0;
    }

    ll maxSum1=(k-1)*n;//都没有达到阈值的时候，最高的那个的和

    ll minSumK=K*n;//所有人都到达阈值后

    if(m<=maxSum1 || m>= minSumK){
        //绝对可以的
        if(m<=maxSum1){
            //m一定大于任何一个元素
            ll diff=m-val.back();
            cout<<diff<<endl;
            return 0;//
        }
        else{
            ll cnt=0;
            for(int i=0;i<n;i++){
                cnt+=(k-val[i]);
            }
            //所有人达到阈值变为K后
            ll diff=m-minSumK;
            cout<<cnt+diff<<endl;
            return 0;//答案必然是这样
        }
    }
    //走到这说明落到了中间
    bool ok=false;
    ll curCnt=0;//达到阈值的个数

    for(int curCnt=1;curCnt<=n;curCnt++){
        //计算当前情况对应的能力上下界
        //不对！当前点可以是任何点！会达到n方炸掉
    }


    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.