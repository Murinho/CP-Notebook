//Tested with: https://cses.fi/problemset/task/2129
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define rofe(i,a,b) for(ll i=a-1;i>=b;--i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define lsbpos(x) __builtin_ffs(x)
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second
#define RB(x) (x<n?r[x]:0)
 
using namespace std;

const ll maxn = 600;
const ll maxm = 50000;
const ll INF = 1e18;

int n,p[maxn],edgeId=1,src,sink;
ll d[maxn], cap[maxn][maxn], cost[maxn][maxn];
bool inq[maxn], vis[maxm];
vi path, g[maxn];

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
    while(flow < n){ //set N equal to INF if wanting to compute the MCMF.
        bellman_ford();
        if(d[sink] == INF) break;

        ll aug = n-flow;
        int u = sink;
        while(u != 0){
            Edge e = (p[u] < 0 ? redges[-p[u]] : edges[p[u]]);
            aug = min(aug, e.r);
            u = e.u;
        }

        flow += aug;
        cost += aug * d[sink];
        u = sink;
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
    return (flow < n ? -1 : cost);
}

void dfs(int u = 0){ //look for all paths computed.
    if(u == sink)  return;
    if(u != 0) path.pb(u);
    for(int i : g[u]){
        if(i > 0 && edges[i].r == 0 && !vis[i]){
            vis[i] = true;
            dfs(edges[i].v);
            return;
        }
    }
}

void add_edge(int u, int v, ll cost){ // u -> v
    g[u].pb(edgeId);
    g[v].pb(-edgeId);
    edges[edgeId] = {u, v, 1, cost};
    redges[edgeId] = {v, u, 0, -cost};
    edgeId++;
}

int main(){
    fast;
    cin>>n;
    src=0, sink=2*n+1;
    // Add normal edges.
    fore(i,1,n+1){
        fore(j,n+1,2*n+1){
            int c;
            cin>>c;
            add_edge(i,j,c);
        }
    }
    fore(i,1,n+1) add_edge(src,i,0); // from src to node.
    fore(i,n+1,2*n+1) add_edge(i,sink,0); // from node to sink.

    cout<<mcf()<<nl;
    fore(i,0,n){
        path.clear();
        dfs();
        cout<<path[0]<<" "<<path[1]-n<<nl;
    }
    return 0;
}