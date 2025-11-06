// Tell if 2 unrooted trees are isomorphically equal
vi center(int n, vvi &adj) {
	int deg[n+1] = {0};
	virtual v;
	for (int i = 1; i <= n; i++) {
		deg[i] = sz(adj[i]);
		if (deg[i] == 1)
			v.pb(i), deg[i]--;
	}
	int m = sz(v);
	while(m < n) {
		vi vv;
		for (auto i: v) {
			for (auto j: adj[i]) {
				deg[j]--;
				if (deg[j] == 1)
					vv.pb(j);
			}
		}
		m += sz(vv);
		v = vv;
	}
	return v;
}
map<vi, ll> mp;
int idx = 0;
 
int dfs(int s, int p, vvi &adj) {
	vi v;
	for (auto i: adj[s]) {
		if (i != p) 
			v.pb(dfs(i, s, adj));
	}
	sort(ALL(v));
	if (!mp.count(v)) mp[v] = idx++;
	return mp[v];
}

void doit(){
	// build adjacency lists (1-indexed nodes).
	vi v1 = center(n,adj), v2 = center(n,adj2);
	bool flag = false;
	int s1 = dfs(v1[0], -1, adj);
		for(auto s : v2){
		int s2 = dfs(s, -1, adj2);
		if (s1 == s2){
			flag=true;
			break;
		}
	}
	cout<<(flag ? "YES" : "NO")<<nl;
}