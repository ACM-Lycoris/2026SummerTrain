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

    vector<int> a(n);
    iota(a.begin(),a.end(),1);

    int pos=0;
    while(a.size()>1){
        pos = (pos+k-1)%a.size();
        a.erase(a.begin()+pos);
        k++;
    }
    cout<<a[0];

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.