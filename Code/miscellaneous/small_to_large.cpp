const ll maxn = 2e5+5;
ll n,res[maxn];
vi adj[maxn];
set <ll> colors[maxn];
 
void dfs(int anode, int node){ //amount of distinct elements in a subtree.
    for(auto au : adj[node]){
        if (anode != au){
            dfs(node,au);
            //current node's set should always be the larger one.
            if (sz(colors[node]) < sz(colors[au])){
                swap(colors[node],colors[au]);
            }
            for(auto elm : colors[au]) colors[node].insert(elm); 
        }
    }
    res[node] = sz(colors[node]);
}