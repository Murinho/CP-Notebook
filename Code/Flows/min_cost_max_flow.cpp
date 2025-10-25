const ll inf = 1e18+7;

struct FlowGraph {
 
	struct Edge {
		ll to, flow, cap, cost;
		Edge *res;
 
		Edge () : to(0), flow(0), cap(0), cost(0), res(0) {}
		Edge (ll to, ll flow, ll cap, ll cost) : to(to), flow(flow), cap(cap), cost(cost), res(0) {}
	
		void addFlow (ll f) {
			flow += f;
			res->flow -= f;
		}
	};
 
 	ll n;
	vector<vector<Edge*>> adj;
	vi dis, pos;
	
 
	FlowGraph (int n) : n(n), adj(n), dis(n), pos(n) {} 
 
	void add (int u, int v, ll cap, ll cost) {
		Edge *x = new Edge(v, 0, cap, cost);
		Edge *y = new Edge(u, cap, cap, -cost);
		x->res = y;
		y->res = x;
		adj[u].pb(x);
		adj[v].pb(y);
	}
 
	pii mcmf(int s, int t, ll tope) {
		vector<bool> inq(n);
		vi dis(n), cap(n);
		vector<Edge*> par(n);
		ll maxFlow = 0, minCost = 0;
 
		while (maxFlow < tope) { //  compute MCF: maxflow < tope, compute MCMF maxflow < inf 
			fill(ALL(dis), inf);
			fill(ALL(par), nullptr);
			fill(ALL(cap), 0);
			dis[s] = 0;
			cap[s] = inf;
			queue<int> q;
			q.push(s);
 
			while (sz(q)) {
				int u = q.front();
				q.pop();
				inq[u] = 0;
 
				for (Edge *v : adj[u]) {
					if (v->cap > v->flow && dis[v->to] > dis[u] + v->cost) {
						dis[v->to] = dis[u] + v->cost;
						par[v->to] = v;
						cap[v->to] = min(cap[u], v->cap - v->flow);
						
						if (!inq[v->to]) {
							q.push(v->to);
							inq[v->to] = 1;
						}
					}
				}
			}
 
			if (!par[t]) break;
 
			maxFlow += cap[t];
			minCost += cap[t] * dis[t];
			for (int u = t; u != s; u = par[u]->res->to)
				par[u]->addFlow(cap[t]);
		}
 
		return {maxFlow, minCost};
	}
};

void doit(){
	// define src and sink.
	// edges src to node, and node to sink have cost 0.
	// to compute flow matches (e.g assignment problems), run dfs over the flow graph, keep the path and substract one unit of flow every time.
}