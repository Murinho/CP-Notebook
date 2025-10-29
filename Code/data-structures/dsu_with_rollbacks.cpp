struct dsu_save {
	int v, rnkv, u, rnku;
		
	dsu_save() {}
	dsu_save(int v, int rnkv, int u, int rnku)
		: v(v), rnkv(rnkv), u(u), rnku(rnku) {}
};

struct dsu_with_rollbacks {
	vi p, rnk;
	int comps;
	stack<dsu_save> op;

	dsu_with_rollbacks() {}
	dsu_with_rollbacks(int n) {
		p.resize(n);
		rnk.resize(n);
		fore(i,0,n){
			p[i] = i;
			rnk[i] = 0;
		}
		comps = n;
	}

	int find_set(int v){
		return (v == p[v]) ? v : find_set(p[v]);
	}
	bool unite(int v, int u){
		v = find_set(v);
		u = find_set(u);
		if (v == u) return false;
		comps--;
		if (rnk[v] > rnk[u]) swap(v, u);
		op.push(dsu_save(v, rnk[v], u, rnk[u]));
		p[v] = u;
		if (rnk[u] == rnk[v]) rnk[u]++;
		return true;
	}
	void rollback(){
		if (op.empty()) return;
		dsu_save x = op.top();
		op.pop();
		comps++;
		p[x.v] = x.v;
		rnk[x.v] = x.rnkv;
		p[x.u] = x.u;
		rnk[x.u] = x.rnku;
	}
};

struct query {
	int v, u;
	bool united;
	query(int _v, int _u) : v(_v), u(_u) {}
};

struct QueryTree {
	vector<vector<query>> t;
	dsu_with_rollbacks dsu;
	int T;

	QueryTree() {}
	QueryTree(int T, int n) : T(T) {
		dsu = dsu_with_rollbacks(n);
		t.resize(4 * T + 4);
	}

	void add_to_tree(int v, int l, int r, int ul, int ur, query& q) {
		if (ul > ur)
			return;
		if (l == ul && r == ur) {
			t[v].pb(q);
			return;
		}
		int mid = (l+r)/2;
		add_to_tree(2 * v, l, mid, ul, min(ur, mid), q);
		add_to_tree(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
	}
	void add_query(query q, int l, int r) {
		add_to_tree(1, 0, T - 1, l, r, q);
	}
	void dfs(int v, int l, int r, vi& ans) {
		for (query& q : t[v]) {
				q.united = dsu.unite(q.v, q.u);
		}
		if (l == r)
				ans[l] = dsu.comps;
		else {
				int mid = (l + r) / 2;
				dfs(2 * v, l, mid, ans);
				dfs(2 * v + 1, mid + 1, r, ans);
		}
		for (query q : t[v]) {
				if (q.united) dsu.rollback();
		}
	}
	vi solve() {
		vi ans(T);
		dfs(1, 0, T - 1, ans);
		return ans;
	}
};

void doit(){
	QueryTree qt(total_time,amount_nodes); // Time and nodes are 0-indexed.
	query edge(x,y); // Existing edge (bidirectional edge)
	// Add the living interval of an edge [l,r]. Close all edges.
	qt.add_query(edge,l,r); 
	// Answer queries: amount of CCs at each moment i.
	vi ans = qt.solve(); 
}