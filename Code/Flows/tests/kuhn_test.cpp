// Problem: Combination Lock (AC) --> https://codeforces.com/gym/104686/problem/B
#include <bits/stdc++.h>
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
#pragma GCC target("popcnt")
 
using namespace std;

int fn,sn;
vector <bool> used;
vector <int> mt;
vvi g;

void init(){
	g.clear(), g.resize(fn);
}

bool kuhn(int v){
	if (used[v]) return false;
	used[v]=true;
	for(int to : g[v]){ //simple adjacency list.
		if (mt[to] == -1 || kuhn(mt[to])){
			mt[to]=v;
			return true;
		}
	}
	return false;
}

ll do_kuhn(){  //Complexity: O(n*m)
	mt.assign(sn,-1); //sn is the size of the second (right) part size of the graph.
	ll mm = 0;
	fore(v,0,fn){ //fn is the size of the first(left) part size of the graph.
		used.assign(fn,false);
		if(kuhn(v)) mm++;
	}
	
	/* mt[i] this is the number of the vertex of the first part connected by an edge 
	with the vertex i of the second part (or -1, if no matching edge comes out of it). */
	/*
	fore(i,0,sn){
		if (mt[i] != -1) cout<<"Connection: "<<mt[i] + 1<<" (left part) -- > "<<i + 1<<" (right part)"<<nl;	
	} */
	
	return mm; //maximum matching.
}

void solve(){
	int n,m;
	string s,t;
	set <int> blocked;
	cin>>n>>m;
	fn = (1<<n); //first (left) part size of the graph.
	sn = (1<<n); //second (right) part size of the graph.
	init();
	cin>>s;
	cin>>t;
	int stmk = 0; //start mask
	fore(i,0,n){
		if (s[i] == t[i]) stmk += (1<<i);
	}
	int stmkpc = __builtin_popcount(stmk);
	
	// read the unreachable states:
	fore(i,0,m){
		cin>>t;
		int x = 0;
		fore(j,0,n) if (t[j] == '=') x += (1<<j);
		blocked.insert(x);
	}
	
	// connect between them excluding the starting node.
	fore(i,0,(1<<n)){
		ll pci = __builtin_popcount(i);
		if (i == stmk || (stmkpc%2) != (pci%2) || blocked.count(i)) continue;
		fore(j,0,(1<<n)){
			ll pcj = __builtin_popcount(j);
			ll x = __builtin_popcount(i^j);
			if (!blocked.count(j) && x == 1 && (pcj%2) != (pci%2)){
				g[i].pb(j); //left part node to right part node g[left_part_node].pb(right_part_node);
			}
		}
	}
	
	ll mm = do_kuhn(); //maximum matching without the starting node.
	
	// connect with the starting node (stmk):
	fore(i,0,(1<<n)){
		ll pci = __builtin_popcount(i);
		ll x = __builtin_popcount(stmk^i);
		if (!blocked.count(i) && x == 1 && (stmkpc%2) != (pci%2)){
			g[stmk].pb(i);
		}
	}
	
	ll mm2 = do_kuhn(); //maximum matching with the starting node.
	
	if (mm != mm2) cout<<"Alice"<<nl;
	else cout<<"Bob"<<nl;
}

int main(){
    fast;
	ll tc;
	cin>>tc;
	while(tc--){ solve();}
}