ll n;
vvi alt;  // alternating directed graph
bool visAlt[maxn]; 
vector<pii> edgesInput;

void dfs_alt(int v) {
	visAlt[v] = true;
	for (int u : alt[v]) if (!visAlt[u]) dfs_alt(u);
}

void doit(){
	// build the network graph.
	// run dinic

	// Build alternating digraph from the matching:
	// - unmatched edges: L -> R
	// - matched edges:   R -> L
	alt.assign(tam, {});
	vector<bool> matchedL(tam, 0), matchedR(tam, 0);

	for (auto &E : dinic.edges) {
		int v = E.v, u = E.u;
		if (v == src || v == sink || u == src || u == sink) continue; // skip src/snk edges
		if (v <= n && n < u) {
			if (E.flow == 1) {
				// matched L-R edge => R -> L in alternating graph
				alt[u].pb(v);
				matchedL[v] = 1; matchedR[u] = 1;
			} else {
				// unmatched L-R edge => L -> R
				alt[v].pb(u);
			}
		}
	}

	// Z = vertices reachable from all UNMATCHED vertices in L
	fore(v,1,n+1){
		if (!matchedL[v] && !visAlt[v]) dfs_alt(v);
	}

	vi cover;
	for (int v = 1; v <= 2*n; v++) {
		if (v <= n) {
			if (!visAlt[v]) cover.pb(v);
		} else {                       
			if (visAlt[v])  cover.pb(v);
		}
	}
}