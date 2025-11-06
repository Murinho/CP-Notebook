// Tell if 2 rooted trees are isomorphically equal
const ll maxn = 2e5+100;
map <vector <ll>, ll> mp;
ll idx=1;

int dfs(int anode, int node, vector < vector <ll> > &adj){
	vector <ll> v;
	for(auto au : adj[node]){
		if (anode != au) v.pb(dfs(node,au,adj));
	}
	sort(ALL(v));
	if (!mp.count(v)) mp[v] = idx, idx++;
	return mp[v];
}

void doit(){
	ll tree1 = dfs(1,1,adj);
	ll tree2 = dfs(1,1,adj2);
	cout<<(tree1 == tree2 ? "Same" : "Diff")<<nl;
}