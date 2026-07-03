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
    
    vector<int> a(n+1);//Left
    vector<int> b(n+1);//Right
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }

    set<int> alive;
    vector<int> dist(n+1,-1);
    queue<int> q;

    for(int i=1;i<=n;i++){
        alive.insert(i);
    }

    dist[n]=0;
    q.push(n);

    int ans=-1;
    while(!q.empty()){
        
        int x=q.front();
        q.pop();

        int L=x-a[x];
        int R=x;

        if(L<=0){
            ans=dist[x]+1;
            break;
        }

        L=max(1,L);

        auto it = alive.lower_bound(L);
        while(it!=alive.end() && *it<=R){
            //有存在的J且小于R
            int j=*it;
            it= alive.erase(it);//删除it当前指向的元素，并让it指向下一个元素直到小于R
            int to = j+b[j];
            if(to>=1 && to<=n && dist[to]==-1){
                dist[to]=dist[x]+1;
                q.push(to);
            }
        }
    }

    cout<<ans<<endl;



    return 0;
}
