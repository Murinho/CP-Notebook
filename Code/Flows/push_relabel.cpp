struct PushRelabel {
	struct Edge {
		int dest, back;
		ll f, c;
		Edge(int dest, int back, ll f, ll c) : dest(dest), back(back), f(f), c(c) {}
	};
	vector<vector<Edge>> g;
	vector<ll> ec;
	vector<Edge*> cur;
	vector<vi> hs; vi H;
	int s, t, S, T;
	PushRelabel(int n, int s, int t, int S, int T) : g(n), ec(n), cur(n), hs(2*n), H(n), s(s), t(t), S(S), T(T) {}
 
	void addEdge(int u, int v, ll cap, ll rcap=0) {
		if (s == t) return;
		g[u].push_back({v, int(sz(g[v])), 0, cap});
		g[v].push_back({u, int(sz(g[u]))-1, 0, rcap});
	}
 
	void addEdgeWithDemands(int u, int v, ll L, ll R) {
		addEdge(S, v, L);
		addEdge(u, T, L);
		addEdge(u, v, R - L);
	}
 
	void addFlow(Edge& e, ll f) {
		Edge &back = g[e.dest][e.back];
		if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
	ll calc() {
		// to obtain the minimal flow with demands, binary search with this value to find the smallest one that provides the maxflow with demands.
		addEdge(t, s, LLONG_MAX); 
		int v = sz(g); H[S] = v; ec[T] = 1;
		vi co(2*v); co[0] = v-1;
		fore(i,0,v) cur[i] = g[i].data();
		for (Edge& e : g[S]) addFlow(e, e.c);
 
		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ec[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0)  // discharge u
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = 1e9;
					for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
						H[u] = H[e.dest]+1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						fore(i,0,v) if (hi < H[i] && H[i] < v)
							--co[H[i]], H[i] = v + 1;
					hi = H[u];
				} else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
					addFlow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
		}
	}
	bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

void doit(){
	ll source=0, sink=1, source_prime = 2, sink_prime = 3;
	PushRelabel flow(graph_size + 4,source,sink,source_prime,sink_prime);

	// Only source and sink will be used in the manual connections, do not use source_prime or sink_prime
}