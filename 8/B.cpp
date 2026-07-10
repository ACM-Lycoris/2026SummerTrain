// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    } 

    int cnt1=0,cnt2=0;//大小大和小大小


    for(int i=1;i<n;i++){
        if(i&1){
            if (a[i]>=a[i-1]){
                cnt1++;
                i++;
            }
        }else{
            if(a[i]<=a[i-1]){
                cnt1++;
                i++;
            }
        }
    }

    for(int i=1;i<n;i++){
        if(i&1){
            if(a[i]<=a[i-1]){
                cnt2++;
                i++;
            }
        }else{
            if(a[i]>=a[i-1]){
                cnt2++;
                i++;
            }
        }
    }
    
    cout<<min(cnt1,cnt2)<<endl;

    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.