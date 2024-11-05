const int maxn = 2e5+5;
int n,m,indeg[maxn];
vi adj[maxn];
vi topo;

void topo_sort(){
    // 1. Create adjacency list with nodes' indegree.
    queue <int> q;
    fore(i,0,n) if (!indeg[i]) q.push(i);
    while (!q.empty()){
        int node = q.front();
        q.pop();
        topo.pb(node);
        for(auto signode : adj[node]){
            indeg[signode]--;
            if (!indeg[signode]) q.push(signode);
        }
    }
} // If sz(topo) != n, there is a cycle in the graph.

