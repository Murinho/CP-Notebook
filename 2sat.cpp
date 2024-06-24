//Tested with: https://codeforces.com/contest/776/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((int)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second

using namespace std;

const ll maxn = 1e5+100;

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
	void add(int u, int v) { // OR = true (u or v is true).
		implication(u, v);
		implication(v, u);
	}
	void diff(int u, int v) { //XOR = true (both u and v are different).
        add(u, v);
        add(neg(u), neg(v));
	}
	void eq(int u, int v) { //XOR = false (both u and v are equal).
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

ll a[maxn];
vector <ll> togs[maxn];

int main(){
    fast;
	ll n,m;
    cin>>n>>m;
    Sat2 sat(m);
	//0: unlocked.
	//1: locked.
    fore(i,0,n) cin>>a[i];

	//insert the togles for each door:
	fore(i,0,m){
		ll k,x;
		cin>>k;
		fore(j,0,k){
			cin>>x, x--;
			togs[x].pb(i);
		}
	}
	fore(i,0,n){
		if (a[i] == 1){ //door is unlocked: needs even amount of toggles.
			sat.eq(togs[i][0],togs[i][1]);
		}
		else{ //door is locked: needs odd amount of toggles.
			sat.diff(togs[i][0],togs[i][1]);
		}
	}
	bool possible = sat.satisfiable();
	if (possible) cout<<"YES"<<nl;
	else cout<<"NO"<<nl;
	return 0;
}