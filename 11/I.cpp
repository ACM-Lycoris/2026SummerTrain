// The answer is in the depth of five fathoms. Waiting to be retrieved.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

int n,m;
vector<vector<int>> graph;
vector<vector<int>> dist;

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

int x,y;

int BFS(int curX,int curY){

    dist.assign(n,vector<int>(m,-1));
    queue<pair<int,int>> q;
    dist[curX][curY]=0;
    q.push({curX,curY});

    while(!q.empty()){
        auto [cx,cy]=q.front(); q.pop();
        for(int d=0;d<4;d++){
            int nx=cx+dx[d], ny=cy+dy[d];
            if(nx<0||nx>=n||ny<0||ny>=m) continue;
            if(graph[nx][ny]==1) continue;      // 障碍
            if(dist[nx][ny]!=-1) continue;
            dist[nx][ny]=dist[cx][cy]+1;
            q.push({nx,ny});
        }
    }
    return dist[n-1][m-1];

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    graph.assign(n, vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>graph[i][j];
        }
    }
    cin>>x>>y;
    cout<<BFS(x-1,y-1)<<endl;
    
    return 0;
}
// The answer is in the depth of five fathoms. And has always been her.