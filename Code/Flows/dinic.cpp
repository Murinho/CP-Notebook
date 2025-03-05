struct FlowEdge {
	int v, u;
	ll cap, flow = 0;
	FlowEdge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};
struct Dinic {
	const ll flow_inf = 1e18;
	vector<FlowEdge> edges;
	vvi adj;
	int n, m = 0;
	int s, t;
	vi level, ptr;
	queue<int> q;
	Dinic(int n, int s, int t) : n(n), s(s), t(t){
		adj.resize(n);
		level.resize(n);
		ptr.resize(n);
	}
	void add_edge(int v, int u, ll cap){ // v -> u
		edges.emplace_back(v, u, cap);
		edges.emplace_back(u, v, 0);
		adj[v].push_back(m);
		adj[u].push_back(m + 1);
		m += 2;
	}
	bool bfs(){
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int id : adj[v]) {
				if (edges[id].cap - edges[id].flow < 1) continue;
				if (level[edges[id].u] != -1) continue;

				level[edges[id].u] = level[v] + 1;
				q.push(edges[id].u);
			}
		}
		return level[t] != -1;
	}
	ll dfs(int v, ll pushed) {
		if (pushed == 0) return 0;
		if (v == t) return pushed;
		for (ll& cid = ptr[v]; cid < sz(adj[v]); cid++) {
			int id = adj[v][cid];
			int u = edges[id].u;
			if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;

			ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
			if (tr == 0) continue;
			
			edges[id].flow += tr;
			edges[id ^ 1].flow -= tr;
			return tr;
		}
		return 0;
	}
	ll flow(){ // run the algorithm.
		ll f = 0;
		while (true) {
			fill(ALL(level), -1);
			level[s] = 0;
			q.push(s);
			if (!bfs()) break;
			fill(ALL(ptr), 0);
			while (ll pushed = dfs(s, flow_inf)) {
				f += pushed;
			}
		}
		return f;
	}
}; // initialize dinic(size,source_index,sink_index).

vector <FlowEdge> fe[maxn];
bool ok;
 
void dfs(int node, vi &path){
	if (node == n-1){ //when reaching the last node.
		ok=true;
		cout<<sz(path)<<nl;
		fore(i,0,sz(path)){
			cout<<path[i]+1<<" ";
		}
		cout<<nl;
		return;
	}
	
	for(auto &e : fe[node]){
		// Conditions of the next node that should be explored:
		if (!ok && e.flow > 0 && e.u < n){ 
			path.pb(e.u);
			e.flow--;
			dfs(e.u,path);
			path.ppb();
		}
	}
}

void doit(){
	// Initialize and build the flow graph.

	// To recover the paths of the flow:
	ll mf = dinic.flow();
	cout<<mf<<nl;
	
	for(FlowEdge e : dinic.edges){
		if (e.flow > 0){
			fe[e.v].pb(e);
		}
	}
	
	vi path;
	fore(i,0,mf){
		ok=false;
		dfs(source,path);
	}
}