#include <bits/stdc++.h>
using namespace std;
inline void optimize()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
}

int main()
{
    optimize();

    int n;
    cin>>n;
    
    vector<int> nums1(n);//Left
    vector<int> nums2(n);//Right
    for(int i=0;i<n;i++){
        cin>>nums1[i];
    }
    for(int i=0;i<n;i++){
        cin>>nums2[i];
    }

    


    return 0;
}
