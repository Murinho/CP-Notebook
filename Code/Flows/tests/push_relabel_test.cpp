// AC: https://codeforces.com/group/TFrGcBYYxs/contest/584448/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
#define ppb pop_back
#pragma GCC target("popcnt")
 
using namespace __gnu_pbds;
using namespace std;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int,null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;

const ll maxn = 2e5+100;

struct PushRelabel{
	struct Edge{
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
		addEdge(t, s, LLONG_MAX); // to obtain the minimal flow with demands, binary search with this value to find the smallest one that provides the maxflow with demands.
		int v = sz(g); H[S] = v; ec[T] = 1;
		vi co(2*v); co[0] = v-1;
		fore(i,0,v) cur[i] = g[i].data();
		for (Edge& e : g[S]) addFlow(e, e.c);
 
		for (int hi = 0;;) {
			while (hs[hi].empty()){
				if (!hi--){
					return -ec[s];
				}
			}
			int u = hs[hi].back(); 
			hs[hi].ppb();
			while (ec[u] > 0){
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = 1e9;
					for (Edge& e : g[u]){
						if (e.c && H[u] > H[e.dest]+1){
							H[u] = H[e.dest]+1, cur[u] = &e;
						}
					}
					if (++co[H[u]], !--co[hi] && hi < v){
						fore(i,0,v){
							if (hi < H[i] && H[i] < v){
								--co[H[i]], H[i] = v + 1;
							}
							
						}
					}
					hi = H[u];
				} 
				else if (cur[u]->c && H[u] == H[cur[u]->dest]+1){
					addFlow(*cur[u], min(ec[u], cur[u]->c));
				}
				else{
					++cur[u];
				}
			}
				
		}
	}
	bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

ll n;
bool ans[maxn];
set <ll> stx,sty;
map <ll,ll> mpx,mpy,cntx,cnty;
map < pii,ll > pindex;
vector <pii> edges;

int main(){
    fast;
	cin>>n;
	fore(i,0,n){
		ll x,y;
		cin>>x>>y;
		edges.pb({x,y});
		stx.insert(x), sty.insert(y);
	}
	
	// map the unique x coordinates:
	for(auto cx : stx){
		mpx[cx] = sz(mpx);
	}
	
	// map the unique y coordinates:
	for(auto cy : sty){
		mpy[cy] = sz(mpy);
	}
	
	fore(i,0,n){
		auto &[x,y] = edges[i];
		x = mpx[x];
		y = mpy[y];
		cntx[x]++;
		cnty[y]++;
		pindex[{x,y}]=i;
	}
	
	ll xn = sz(stx);
	ll yn = sz(sty);
	ll source=0, sink=1, source_prime = 2, sink_prime = 3;
	PushRelabel flow(xn + yn + 4,source,sink,source_prime,sink_prime);
	
	fore(i,0,xn){
		// main source to row (x)
		flow.addEdgeWithDemands(source,i+4,cntx[i]/2,(cntx[i]+1)/2);
	}
	
	fore(i,0,yn){
		// column (y) to main sink
		flow.addEdgeWithDemands(xn+i+4,sink,cnty[i]/2,(cnty[i]+1)/2);
	}
	
	// push normal flow edges:
	for(auto [x,y] : edges){
		flow.addEdge(x+4,y + xn + 4, 1);
	}
	
	ll totf = flow.calc();
	
	fore(i,0,xn){
		for(auto ed : flow.g[i+4]){
			if (ed.dest >= xn + 4 && ed.f > 0){ //si el otro lado de la arista es una columna y por ella pasa flujo (e.f > 0)
				ll cx = i;
				ll cy = ed.dest - xn - 4;
				ans[pindex[{cx,cy}]]=true; //paint this node as 'L', else as 'F'.
			}
		}
	}
	fore(i,0,n) cout<<(ans[i] ? "L" : "F");
	cout<<nl;
	return 0;
}