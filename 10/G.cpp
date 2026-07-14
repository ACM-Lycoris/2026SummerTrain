// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

const double pi = 3.1416;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    vector<ll> a(n);

    ll left=0;ll right=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        left=max(left,a[i]);
        right+=a[i];
    }

    auto check = [&](ll limit) -> bool
    {
        int cnt = 1; // 当前至少需要一个同学
        ll sum = 0;

        for (ll x : a)
        {
            if (sum + x <= limit)
            {
                // 当前同学借的钱还能覆盖这份礼物
                sum += x;
            }
            else
            {
                // 当前同学的钱不够了，找下一个同学
                cnt++;
                sum = x;
            }
        }

        return cnt <= m;
    };

    while(left<right){
        ll mid=left+(right-left)/2;
        if(check(mid)){
            right=mid;
        }else{
            left=mid+1;
        }
    }
    cout<<left<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.