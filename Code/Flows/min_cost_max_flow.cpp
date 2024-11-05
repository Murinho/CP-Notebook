//Tested with: https://cses.fi/problemset/task/2129
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((int)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
 
using namespace std;

const ll maxn = 600;
const ll maxm = 50000;
const ll INF = 1e18;

int N, p[maxn];
ll d[maxn], cap[maxn][maxn], cost[maxn][maxn];
bool inq[maxn], vis[maxm];
vector<int> path, g[maxn];

struct Edge {
    int u, v;
    ll r, c;
} edges[maxm], redges[maxm];

void bellman_ford(int start = 0){
    fill(inq, inq+maxn, false);
    fill(d, d+maxn, INF);
    fill(p, p+maxn, 0);

    queue<int> Q;
    Q.push(start);
    d[start] = 0;
    inq[start] = true;
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        inq[u] = false;

        for(int i : g[u]){
            Edge e = (i < 0 ? redges[-i] : edges[i]);
            if(e.r > 0 && d[e.v] > d[u] + e.c){
                d[e.v] = d[u] + e.c;
                p[e.v] = i;
                if(!inq[e.v]){
                    inq[e.v] = true;
                    Q.push(e.v);
                }
            }
        }
    }
}

ll mcf(){
    ll flow = 0, cost = 0;
    while(flow < N){ //set N equal to INF if wanting to compute the MCMF.
        bellman_ford();
        if(d[2*N+1] == INF) break;

        ll aug = N-flow;
        int u = 2*N+1;
        while(u != 0){
            Edge e = (p[u] < 0 ? redges[-p[u]] : edges[p[u]]);
            aug = min(aug, e.r);
            u = e.u;
        }

        flow += aug;
        cost += aug * d[2*N+1];
        u = 2*N+1;
        while(u != 0){
            if(p[u] < 0){
                redges[-p[u]].r -= aug;
                edges[-p[u]].r += aug;
            } else {
                redges[p[u]].r += aug;
                edges[p[u]].r -= aug;
            }
            u = (p[u] < 0 ? redges[-p[u]].u : edges[p[u]].u);
        }
    }
    return (flow < N ? -1 : cost);
}

void dfs(int u = 0){
    if(u == 2*N+1)  return;
    if(u != 0)      path.push_back(u);
    for(int i : g[u]){
        if(i > 0 && edges[i].r == 0 && !vis[i]){
            vis[i] = true;
            dfs(edges[i].v);
            return;
        }
    }
}

int main(){
    fast;
    cin>>N;
    int edgeID = 1;
    for(int u = 1; u <= N; u++){
        for(int v = N+1, c; v <= 2*N; v++){
            cin>>c;
            g[u].push_back(edgeID);
            g[v].push_back(-edgeID);
            edges[edgeID] = {u, v, 1, c};
            redges[edgeID] = {v, u, 0, -c};
            edgeID++;
        }
    }
    for(int v = 1; v <= N; v++){
        g[0].push_back(edgeID);
        g[v].push_back(-edgeID);
        edges[edgeID] = {0, v, 1, 0};
        redges[edgeID] = {v, 0, 0, 0};
        edgeID++;
    }
    for(int u = N+1; u <= 2*N; u++){
        g[u].push_back(edgeID);
        g[2*N+1].push_back(-edgeID);
        edges[edgeID] = {u, 2*N+1, 1, 0};
        redges[edgeID] = {2*N+1, u, 0, 0};
        edgeID++;
    }

    cout<<mcf()<<nl;
    for(int i = 0; i < N; i++){
        path.clear();
        dfs();
        cout<<path[0]<<" "<<path[1] - N<<nl;
    }
    return 0;
}