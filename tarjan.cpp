#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fast cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
#define nl '\n'
 
using namespace std;
 
const ll maxn = 2e5+10;
ll n,x,y,m,foundat;
ll low[maxn],disc[maxn],isArt[maxn],inStack[maxn];
vector <ll> adj[maxn];
vector < vector <ll> > scc;
vector < pair <ll,ll> > brid;
 
void dfs(int node, int antnode) {
    static stack <int> stk;
    low[node] = disc[node] = foundat;
    stk.push(node);
    inStack[node] = 1;
    foundat++;
    int children = 0;
    for (auto signode : adj[node]){
        if(disc[signode] == 0){
            children++;
            dfs(signode, node);
            if (low[signode] > disc[node]){
                brid.pb({node,signode});
            }
            low[node] = min(low[node], low[signode]);
            if (antnode == -1 && children > 1) isArt[node] = 1;
            if (antnode != -1 && low[signode] >= disc[node]) isArt[node] = 1;
        }
        //Remove some of this IF condition according to the desired function of Tarjan
        //When wanting to find SCC's:
        else if (inStack[signode] == 1){
            low[node] = min(low[node], disc[signode]);
        } 
        //When wanting to find bridges: 
        /*
        else if (antnode != signode){
            low[node] = min(low[node], disc[signode]);
        } */
    }
    if (low[node] == disc[node]){
        vector <ll> scctem;
        while (true){
            ll topic = stk.top();
            stk.pop();
            scctem.pb(topic);
            inStack[topic] = 0;
            if (node == topic) break;
        }
        scc.pb(scctem);
    }
}
 
void tarjan(ll stnode) {
    foundat = 1;
    dfs(stnode, -1);
}

int main(){
    fast;
    cin>>n>>m; //amount of nodes and edges:
    init();
    for (int i = 1; i<=m; i++){
        ll x,y;
        cin>>x>>y;
        adj[x].pb(y);
    }
    for (int i = 1; i<=n; i++){
        if (disc[i] == 0) tarjan(i);
    }
    return 0;
}