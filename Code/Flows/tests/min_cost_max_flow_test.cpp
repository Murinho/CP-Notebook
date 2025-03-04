// AC. Tested with: https://cses.fi/problemset/task/2129/
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
 
using namespace __gnu_pbds;
using namespace std;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int,null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;

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

vvi paths;
int n,source,sink;

void find_paths(int node, vi &path, FlowGraph &g){
	if (node == sink){
		paths.pb(path);
		return;
	}
	
	for(auto e : g.adj[node]){
		if (e->flow > 0 && e->to != source){ //Follow edges where there was a flow
			if (sz(path) == 0 && e->to < n){
				path.pb(e->to);
				e->flow--;
				find_paths(e->to,path,g);
				path.pop_back();
			}
			else if (sz(path) == 1 && e->to >= n){
				path.pb(e->to);
				e->flow--;
				find_paths(e->to,path,g);
				path.pop_back();
			}
			else if (sz(path) == 2 && e->to == sink){
				path.pb(e->to);
				e->flow--;
				find_paths(e->to,path,g);
				path.pop_back();
			}
		}
	}
}

void solve(){
	cin>>n;
	FlowGraph g(n + n + 2);
	source = n + n;
	sink = source + 1;
	fore(i,0,n){
		fore(j,n,n+n){
			ll x;
			cin>>x;
			g.add(i,j,1,x);
		}
		
		g.add(source,i,1,0); // from source to person.
		g.add(i + n,sink,1,0); // from task to sink.
	}
	
	ll ans = g.mcmf(source,sink,n).snd;
	
	vi path;
	find_paths(source,path,g);
	cout<<ans<<nl;
	for(auto &p : paths){
		cout<<p[0]+1<<" "<<p[1]-n+1<<nl;
	}
	return;
}

int main(){
    fast;
    ll tc = 1;
    while(tc--){
        solve();
    }
}