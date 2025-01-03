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

void dfs(int u = 0){ //look for all paths computed (flow matches).
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

void doit(){
    // define src and sink.
    // edges src to node, and node to sink have cost 0.
    // to compute flow matches, run dfs n times (amount of left side nodes).
}