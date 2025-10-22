// Tested with AC: https://cses.fi/problemset/task/1709/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define rofe(i,a,b) for(ll i=a-1;i>=b;--i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define lsbpos(x) __builtin_ffs(x)
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second
#define eb emplace_back
#define ppb pop_back
#define i128 __int128_t
#define ull unsigned long long
 
using namespace __gnu_pbds;
using namespace std;

const ll maxn = 205;

struct FlowEdge {
	int v, u;
	ll cap, flow = 0;
	FlowEdge(int v, int u, ll cap) : v(v), u(u), cap(cap) {}
};
struct Dinic {
	const ll flow_inf = 1e18;
	vector<FlowEdge> edges;
	vvi adj;
	int n, m = 0;
	int s, t;
	vi level, ptr;
	queue<int> q;
	Dinic(int n, int s, int t) : n(n), s(s), t(t){
		adj.resize(n);
		level.resize(n);
		ptr.resize(n);
	}
	void add_edge(int v, int u, ll cap){ // v -> u
		edges.emplace_back(v, u, cap);
		edges.emplace_back(u, v, 0);
		adj[v].push_back(m);
		adj[u].push_back(m + 1);
		m += 2;
	}
	bool bfs(){
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int id : adj[v]) {
				if (edges[id].cap - edges[id].flow < 1) continue;
				if (level[edges[id].u] != -1) continue;

				level[edges[id].u] = level[v] + 1;
				q.push(edges[id].u);
			}
		}
		return level[t] != -1;
	}
	ll dfs(int v, ll pushed) {
		if (pushed == 0) return 0;
		if (v == t) return pushed;
		for (ll& cid = ptr[v]; cid < sz(adj[v]); cid++) {
			int id = adj[v][cid];
			int u = edges[id].u;
			if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;

			ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
			if (tr == 0) continue;
			
			edges[id].flow += tr;
			edges[id ^ 1].flow -= tr;
			return tr;
		}
		return 0;
	}
	ll flow(){ // run the algorithm.
		ll f = 0;
		while (true) {
			fill(ALL(level), -1);
			level[s] = 0;
			q.push(s);
			if (!bfs()) break;
			fill(ALL(ptr), 0);
			while (ll pushed = dfs(s, flow_inf)) {
				f += pushed;
			}
		}
		return f;
	}
}; // initialize dinic(size,source_index,sink_index).

ll n;
vvi alt;  // alternating directed graph
bool visAlt[maxn]; 
vector<pii> edgesInput;

void dfs_alt(int v) {
    visAlt[v] = true;
    for (int u : alt[v]) if (!visAlt[u]) dfs_alt(u);
}


int main(){
    fast;
    cin >> n;
    int src = 0;
    int sink = 2*n + 1;
    int tam = (2*n)+2;
    
    Dinic dinic(tam,src,sink);
    
    fore(i,1,n+1){ 
    		fore(j,1,n+1){
	    		char c;
	    		cin >> c;
	    		if (c == 'o'){
	    			dinic.add_edge(i,j+n,1);
	    			edgesInput.eb(i,j+n);
	    		}
	    	}
	    	dinic.add_edge(src,i,1);
	    	dinic.add_edge(i+n,sink,1);
    }
    
    ll mf = dinic.flow(); // max flow = min vertex cover
    
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

    // C = (L \ Z) ∪ (R ∩ Z)
    vi cover;
    for (int v = 1; v <= 2*n; v++) {
        if (v <= n) {
            if (!visAlt[v]) cover.pb(v);
        } else {                       
            if (visAlt[v])  cover.pb(v);
        }
    }

	cout << mf << nl;
    for (auto &node : cover){
    		if (node <= n) cout << 1 << " " << node << nl;
    		else cout << 2 << " " << node - n << nl;
    }
    return 0;
    cout << nl;
}