#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

ll n,m,x,y,w;
const ll INF = 1e18;
vector < vector < pair <int,int> > > adj;
vector <ll> dis;
priority_queue< pair <ll,ll> , vector< pair <ll,ll> >, greater< pair <ll,ll> > > pq;

void init(){
    dis.assign(n+1,INF);
    adj.resize(n+1);
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin>>n>>m; //N: number of nodes, M: number of edges.
    init();
    for (int i = 1; i<=m; i++){
        cin>>x>>y>>w;
        adj[x].pb({y,w});
    }
    //Do Dijkstra:
    pq.push({0,1}); //first: weight, second: node.
    dis[1] = 0;
    while(!pq.empty()){
        ll node = pq.top().second;
        ll w = pq.top().first;
        pq.pop();
        if (dis[node] < w) continue;
        for (auto i : adj[node]){
            ll signode = i.first;
            ll weight = i.second;
            if (dis[signode] > dis[node] + weight){
                dis[signode] = dis[node] + weight;
                pq.push({dis[signode],signode});
            }
        }
    }
    //Minimum distance to all nodes from the source node
    for (int i = 1; i<=n; i++){
        if (dis[i+n] >= INF) cout<<-1<<" ";
        else cout<<dis[i+n]<<" ";
    }
    cout<<"\n";
    return 0;
}