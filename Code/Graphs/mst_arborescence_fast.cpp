/* Computes minimum spanning arborescence (directed MST) rooted at a give node.
  Nodes are 0..n-1.
  Complexity: O(m*log(m) + n*log(m)) 

  For unrooted problems, one can create a mock node and connect it to every
  other node with weight = infinity (be careful with having a big enough
  infinity value but not super big as one has to avoid overflow)
*/  
struct RollbackUF{
	vi e; vector<pii> st;
	RollbackUF(int n): e(n, -1) {}
	int size(int x){ return -e[find(x)]; }
	int find(int x){ return e[x] < 0 ? x : find(e[x]); }
	int time(){ return sz(st); }
	void rollback(int t){
		for(int i = time(); i --> t;) e[st[i].f] = st[i].s;
		st.resize(t);
	}
	bool join(int a, int b){
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a,b);
		st.pb({a,e[a]});
		st.pb({b,e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};
  
struct Edge { ll u,v,w; };

struct Node{
	Edge key;
	Node *l, *r;
	ll delta;
	void prop(){
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top(){ prop(); return key; }
};

Node *merge(Node *a, Node *b){
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a,b);
	swap(a->l, (a->r = merge(b,a->r)));
	return a;
}

void pop(Node*& a){
	a->prop();
	a = merge(a->l, a->r);
}

ll dmst(int n, int r, vector<Edge> &g){
	RollbackUF uf(n);
	vector<Node*> heap(n);
	for (Edge e : g) heap[e.v] = merge(heap[e.v], new Node{e});
	
	ll res = 0;
	vi seen(n,-1), path(n), par(n);
	
	seen[r] = r;
	vector <Edge> Q(n), in(n,{-1,-1}), comp;
	deque < tuple <int, int, vector <Edge> > > cycs;
	
	fore(s,0,n){
		int u = s, qi = 0, w;
		while(seen[u] < 0){
			if (!heap[u]) return -1;
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			Q[qi] = e, path[qi++] = u, seen[u] = s;
			res += e.w, u = uf.find(e.u);
			
			if (seen[u] == s){
				Node *cyc = 0;
				int end = qi, time = uf.time();
				do cyc = merge(cyc,heap[w = path[--qi]]);
				while(uf.join(u,w));
				u = uf.find(u), heap[u] = cyc, seen[u] = -1;
				cycs.push_front({u, time, {&Q[qi], &Q[end]}});
			}
		}
		fore(i,0,qi) in[uf.find(Q[i].v)] = Q[i];
	}
	return res;
}

void doit(){
    // read graph and push edges as {u,v,w}, u and v are nodes and w is the weight of the edge.
    ll res = dmst(n,0,g); // where edges [0,n-1]
    cout << res << nl;
}