const int maxn = 1e5+5;

ll n,m,indeg[maxn],outdeg[maxn];
vi g[maxn],path;

// Hierholzer's algorithm
// Directed graph: going from node 1, passing through all edges without repeating and end at node n.
void dfs(int node){
	while(!g[node].empty()){
		int signode = g[node].back();
		g[node].pop_back();
		dfs(signode);
	}
	path.pb(node);
}

void doit(){
	//Have out and in degree for each node first.
	bool flag=true;
	fore(i,2,n) if (indeg[i] != outdeg[i]) flag=false;
	if (indeg[1]+1 != outdeg[1] || indeg[n]-1 != outdeg[n] || !flag){
		cout<<"IMPOSSIBLE"<<nl;
		return;
	}
	dfs(1);
	reverse(ALL(path));
	if (sz(path) != m+1 || path.back() != n) cout<<"IMPOSSIBLE"<<nl;
	else{
		for(auto node : path) cout<<node<<" ";
		cout<<nl;
	}
}