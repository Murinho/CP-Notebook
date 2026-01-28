const ll maxn = 2e5+10;
ll n,x,y,m,timer=0;
ll low[maxn],disc[maxn],isArt[maxn],inStack[maxn];
vi adj[maxn];
vvi scc;
vector < pii > brid;
stack <int> stk; // to find SCCs (directed graphs)
vector <pii> edges; // to find BCCs (undirected graphs)

void extract_bcc_nodes(int stop_u, int stop_v, vi &bcc_nodes){
	while(sz(edges)){
        auto e = edges.back();
        edges.ppb();
        bcc_nodes.pb(e.f);
        bcc_nodes.pb(e.s);
        if ((e.f == stop_u && e.s == stop_v) || (e.f == stop_v && e.s == stop_u)) break;
    }
    sort(ALL(bcc_nodes));
    bcc_nodes.erase(unique(ALL(bcc_nodes)), bcc_nodes.end());
}
 
void dfs(int node, int antnode = -1){
	low[node] = disc[node] = ++timer;
	stk.push(node);
	inStack[node] = 1;
	int children = 0;
	for (auto signode : adj[node]){
		if(disc[signode] == 0){
			children++;
			edges.pb({node,signode});
			dfs(signode, node);

			// To find bridges:
			if (low[signode] > disc[node]){
				brid.pb({node,signode});
			}

			low[node] = min(low[node], low[signode]);

			// To find articulation points (undirected graphs):
			if (antnode == -1 && children > 1) isArt[node] = 1;
			if (antnode != -1 && low[signode] >= disc[node]) isArt[node] = 1;

			// To find BCCs (undirected graphs):
			if (low[signode] >= disc[node]){
				vi bcc_nodes; // stores the nodes from a BCC (in no specific order)
				extract_bcc_nodes(node,signode,bcc_nodes);
			}
		}
		// To find SCC's (directed graphs):
		else if (inStack[signode] == 1){
			low[node] = min(low[node], disc[signode]);
		} 
		// To find articulation points, bridges, and/or BCCs (undirected graphs)
		else if (antnode != signode){
			if (disc[signode] < disc[node]){ // to find BCCs
				edges.pb({node,signode});
			}
			low[node] = min(low[node], disc[signode]);
		} 
	}
	if (low[node] == disc[node]){ // To find SCC's (directed graphs)
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