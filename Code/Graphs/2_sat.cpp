struct Sat2 {
	vector< vector<int> > g, rg;
	vector<int> component;
	vector<bool> ans;
	int tag, n, siz;
	stack<int> st;
	Sat2(int n) : n(n), siz(2*n), g(vector< vector<int> >(2*n)), rg(vector< vector<int> >(2*n)) {}
	void add_edge(int u, int v) {
		g[u].push_back(v);
		rg[v].push_back(u);
	}
	int neg(int u) {
		return (n+u)%siz;
	}
	void implication(int u, int v) {
		add_edge(neg(u), v);
	}
	// AND (a&b) = add(a&a), add(b&b)
	void add(int u, int v) { // OR = true (u or v is true).
		implication(u, v);
		implication(v, u);
	}
	void diff(int u, int v) { //XOR = true (u != v).
		add(u, v);
		add(neg(u), neg(v));
	}
	void eq(int u, int v) { //XOR = false (u == v).
		diff(neg(u), v);
	}
	void dfs(int u, vector< vector<int> > &g, bool first) {
		component[u] = tag;
		for(int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if(component[v] == -1)
				dfs(v, g, first);
		}
		if(first) st.push(u);
	}
	bool satisfiable() {
		tag = 0;
		ans = vector<bool>(n);
		component = vector<int>(siz, -1);
		for(int i = 0; i < siz; i++) {
			if(component[i] == -1)
				dfs(i, g, true);
		}
		component = vector<int>(siz, -1);
		tag = 0;
		while(st.size()) {
			int u = st.top(); st.pop();
			if(component[u] != -1) continue;
			++tag;
			dfs(u, rg, false);
		}
		for(int i = 0; i < n; i++) {
			if(component[i] == component[neg(i)]) return false;
			ans[i] = component[i] > component[neg(i)];
		}
		return true;
	}
};

void doit(){
	ll n;
	Sat2 sat(n);
	// insert clauses ...
	sat.satisfiable(); //run 2-SAT.
}