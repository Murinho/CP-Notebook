const int maxn = 1e5+5;
const int maxm = 2e5+5;

ll seen[maxm],n,m;
vi path;
vector < pii > g[maxn]; //{neighbor node, edge index}

// Hierholzer's algorithm
// Going from node 1, passing through all edges without repeating and come back to node 1.
void dfs(int node){
	while(!g[node].empty()){
		auto [signode, idx] = g[node].back();
		g[node].pop_back();
		if (seen[idx]) continue;
		seen[idx]=true;
		dfs(signode);
	}
	path.pb(node);
}

void doit(){
	// Create adjacency list.
	fore(i,0,n){
		if (sz(g[i])%2){
			cout<<"IMPOSSIBLE"<<nl;
			return;
		}
	}
	dfs(0);
	if (sz(path) != m+1) cout<<"IMPOSSIBLE"<<nl;
	else{
		for(auto node : path) cout<<node+1<<" ";
		cout<<nl;
	}
}