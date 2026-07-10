// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

int qpow2(int i){
    //对a,b来说，a==2,b==i这里
    int a=2;
    int ans=1;
    while(i>0){
        if(i&1)ans=ans*a;
        a*=a;
        i>>=1;
    }
    return ans;
}

const int MAXN=1000006;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>> T;
    
    vector<int> pow2;

    int i=0;
    while(true){
        int tempI=qpow2(i);
        if(tempI<MAXN){
            pow2.emplace_back(tempI);
            i++;
        }else{
            break;
        }
    }
    //cout<<pow2.size()
    while(T--){
        int L,R;
        cin>>L>>R;

        int Len=0;
        
        for(int i=L;i<=R;i*=2){
            //不超过二十次
            Len++;
        }
    //cout<<Len<<endl;

        ll ans=0;
        ll x2=1<<(Len-1);
        ans+=(R/x2)-L+1;

        if(Len>=2){
            ll x3=3*(1<<(Len-2));
            ll start=R/(x3)-L+1;
            if(start>0)
            {
                ans+=(Len-1)*start;
            }
        }

        cout<<Len<<' '<<ans<<'\n';
    }
    
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.