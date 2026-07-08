#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;
using ull = unsigned long long;
using lll = __int128;
ll n;
ll m;
vector<ll> a, b;
bool check(ull t)
{
    lll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        ull J = t / (ull)b[i];
        sum += (lll)a[i] * (lll)(J + 1); // 老师 i 容量 = ai * (J + 1)
        if (sum >= (lll)m){
            return true;
        }
    }
    return false; // 全加完还不够
}

int main()
{
    optimize();

    cin >> n >> m;
    a.assign(n + 1, 0);
    b.assign(n + 1, 0);
    ll maxb = 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
    }

    ull lo = 0, hi = (ull)maxb * (ull)m;

    while (lo < hi)
    {
        ull mid = lo + ((hi - lo) >> 1);
        if (check(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    ull T  = lo;
    ll FT = 0;//时间严格小于T时候的人数

    for(ll i=1;i<=n;i++){
        ull c = (T+(ull)b[i]-1)/(ull)b[i];//ceil(T / b[i])
        FT += (a[i]*c);
    }
    ll Remain=m-FT;//剩下的人

    for(int i=1;i<=n;i++){

        //给每个老师塞人
        ull c=(T+(ull)b[i]-1)/(ull)b[i];
        ll cnt=a[i]*c;

        if(T%b[i]==0){
            ll take=min(Remain,a[i]);
            cnt+=take;
            Remain-=take;
        }
        cout<<cnt<<' ';
    }
    cout<<endl;

    

    return 0;
}