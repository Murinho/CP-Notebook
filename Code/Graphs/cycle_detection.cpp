const ll maxn = 2e5+5;
ll n,m,color[maxn],par[maxn];
vvi cycles;
vi adj[maxn];

void dfs_cycle(int u, int p){
	if (color[u] == 2) return;
	if (color[u] == 1) {
		vi v;
		int cur = p;
		v.pb(cur);
		while (cur != u){
			cur = par[cur];
			v.pb(cur);
		}
		//reverse(ALL(v)); //uncomment if graph is directed.
		cycles.pb(v);
		return;
	}
	par[u] = p;
	color[u] = 1;
	for (int v : adj[u]) {
		if (v == par[u]) { //remove IF graph is directed.
			continue;
		}
		dfs_cycle(v, u);
	}
	color[u] = 2;
}