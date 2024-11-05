const ll maxn = 2e5+10;
ll n,x,y,m,foundat=1;
ll low[maxn],disc[maxn],isArt[maxn],inStack[maxn];
vi adj[maxn];
vvi scc;
vector < pii > brid;
 
void dfs(int node, int antnode){ //first call antnode should be = -1.
    static stack <int> stk;
    low[node] = disc[node] = foundat;
    stk.push(node);
    inStack[node] = 1;
    foundat++;
    int children = 0;
    for (auto signode : adj[node]){
        if(disc[signode] == 0){
            children++;
            dfs(signode, node);
            if (low[signode] > disc[node]){
                brid.pb({node,signode});
            }
            low[node] = min(low[node], low[signode]);
            if (antnode == -1 && children > 1) isArt[node] = 1;
            if (antnode != -1 && low[signode] >= disc[node]) isArt[node] = 1;
        }
        //Remove some of this IF condition according to the desired function of Tarjan
        //When wanting to find SCC's:
        else if (inStack[signode] == 1){
            low[node] = min(low[node], disc[signode]);
        } 
        //When wanting to find bridges or articulation points: 
        /*
        else if (antnode != signode){
            low[node] = min(low[node], disc[signode]);
        } */
    }
    if (low[node] == disc[node]){ // for SCC's
        vi scctem;
        while (true){
            ll topic = stk.top();
            stk.pop();
            scctem.pb(topic);
            inStack[topic] = 0;
            if (node == topic) break;
        }
        scc.pb(scctem);
    }
}