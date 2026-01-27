/* Computes minimum spanning arborescence (directed MST) rooted at a give node.
  Nodes are 0..n-1.
  Returns {ok, cost}. ok=false if not all nodes reachable from root.
  Complexity: O(n*m) */
struct Edge { ll u,v,w; };
pair<bool, ll> mst_arborescence(ll n, ll root, vector<Edge> &edges) {
    ll ans = 0;
    while (1){
        // For each node, pick minimum incoming edge weight
        vi in(n, INF), pre(n, -1);
        for (auto &e : edges) {
            if (e.u != e.v && e.w < in[e.v]) {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }
        in[root] = 0; // root has no incoming edge in the arborescence
        // If any node (except root) has no incoming edge, arborescence impossible
        fore(v,0,n){
            if (v == root) continue;
            if (in[v] == INF) return {false, 0LL};
        }
        // Detect cycles among chosen incoming edges
        int cntCycles = 0;
        vi id(n, -1), vis(n, -1);

        fore(i,0,n){
            ans += in[i];
			// Walk predecessors until we reaching root or a visited node
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            // Found a cycle (not involving root)
            if (v != root && id[v] == -1) {
                for (int x = pre[v]; x != v; x = pre[x]) {
                    id[x] = cntCycles;
                }
                id[v] = cntCycles;
                cntCycles++;
            }
        }
        if (cntCycles == 0) break; // no cycles, done.
        // Assign IDs to non-cycle nodes
        fore(i,0,n) if (id[i] == -1) id[i] = cntCycles++;

        // Build contracted graph with adjusted weights
        vector<Edge> newEdges;
        newEdges.reserve(sz(edges));

        for(auto &e : edges) {
            int u2 = id[e.u], v2 = id[e.v];
            if (u2 == v2) continue;

            // Adjust entering-edge weights: w2 = w - in[v]
            ll w2 = e.w - in[e.v];
            newEdges.pb({u2, v2, w2});
        }

        // Update root and n (amount of nodes in the compressed graph)
        root = id[root];
        n = cntCycles;
        edges = newEdges;
    }
    return {true, ans};
}

void doit(){
	ll n, m, root=0;
    cin >> n >> m;
    vector<Edge> edges;
    edges.reserve(m);
    fore(i,0,m){
        ll u,v,w;
        cin >> u >> v >> w;
        edges.pb({u, v, w});
    }
    auto [ok, ans] = mst_arborescence(n, root, edges);
    if (!ok) cout << "IMPOSSIBLE" << nl;
    else cout << ans << nl;
    return;
}