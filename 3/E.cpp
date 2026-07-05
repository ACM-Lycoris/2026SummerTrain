#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

using ll = long long;

const ll MOD = 1e9 + 7;

string removePre0(string &s)
{
    if (s[0] != '0')
    {
        return s;
    }
    else
    {
        if (s.length() == 1)
        {
            // 只能返回0
            return "0";
        }
        else
        {
            auto it = s.find_first_not_of("0");
            if (it != string::npos)
            {
                string res = s.substr(it);
                return res;
            }
            else
            {
                return "0";
            }
        }
    }
}

string superLowPlus(const string &A, const string &B)
{
    string a = A, b = B;
    if (a.length() < b.length())
    {
        swap(a, b);
    }

    string res = "";
    ll lenA = a.length(), lenB = b.length();
    b = string(lenA - lenB, '0') + b;
    bool ppp = false; // 进位标志
    for (ll i = 0; i < lenA; i++)
    {
        char cA = a[lenA - 1 - i], cB = b[lenA - 1 - i];

        int digA = int(cA - '0'), digB = int(cB - '0');
        int temp = digA + digB + (ppp ? 1 : 0);
        if (temp >= 10)
        {
            temp %= 10;
            ppp = true;
        }
        else
        {
            ppp = false;
        }

        char rC = char(temp + '0'); // result char,要加进结果的字符
        res += rC;
    }
    if (ppp == true)
    {
        // 结束后进位符还在
        res += '1';
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() 
{
    optimize();

    string x;
    cin >> x;
    ll n=x.length();

    vector<ll> pow10(n+1);
    pow10[0]=1;
    for(ll i=1;i<=n;i++){

        pow10[i]=pow10[i-1]*10%MOD;
    }

    //R[x]=R[x-1]+x*10^(x)
    vector<ll> R(n+1);
    R[0]=0;R[1]=1;
    for(ll i=2;i<=n;i++){
        R[i]=(R[i-1]+i*(pow10[i-1]))%MOD;
    }
    
    ll res=0;
    for(ll i=1;i<=n;i++){

        //每个i，枚举左右删除的个数
        ll d = x[i-1]-'0';
        
        ll right=n-i;
        
        //左
        ll leftCnt = i * (i - 1) / 2;
        ll contr = d * (leftCnt * pow10[right] + R[right]) % MOD;

        res=(res+contr)%MOD;
    }

    cout<<res<<endl;
    

    return 0;
}
