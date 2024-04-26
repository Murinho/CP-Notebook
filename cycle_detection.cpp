#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fast cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
#define nl '\n'

using namespace std;

ll tc,n,m,k,ans,best,x,y;
vector < vector <ll> > cycles;
vector < vector <ll> > adj;
vector <ll> color,par;

void init(){
    color.resize(n+1);
    par.resize(n+1);
    adj.resize(n+1);
}

void dfs_cycle(int u, int p)
{
    if (color[u] == 2) {
        return;
    }
    if (color[u] == 1) {
        vector<ll> v;
           
        int cur = p;
        v.push_back(cur);
 
        while (cur != u) {
            cur = par[cur];
            v.push_back(cur);
        }
		//reverse(ALL(v)); //uncomment if graph is directed.
        cycles.pb(v);
        return;
    }
    par[u] = p;
 
    color[u] = 1;
 
    for (int v : adj[u]) {
    	if (v == par[u]) { //remove IF graph is directed.
            continue;
        }
        dfs_cycle(v, u);
    }
    color[u] = 2;
}
 

int main(){
    fast;
	cin>>n>>m;
    init();
    for (int i = 1; i<=m; i++){
        cin>>x>>y;
        adj[x].pb(y);
		adj[y].pb(x);
    }
    for (int i = 1; i<=n; i++) if (color[i] == 0) dfs_cycle(i,0);

    //Print the cycles of the graph:
    for (auto cy : cycles){
        for (auto node : cy){
            cout<<node<<" ";
        }
        cout<<nl;
    }
	return 0;
}