#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fast cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
#define nl '\n'
 
using namespace std;
 
ll n,x,y,m,foundat,rb,k,root,small,indx;
vector <ll> low,disc,isArt,inStack;
vector < vector <ll> > adj,scc;
vector < pair <ll,ll> > brid;
 
void init(){
    disc.clear(), disc.resize(n+1);
    low.clear(), low.resize(n+1);
    isArt.clear(), isArt.resize(n+1);
    adj.clear(), adj.resize(n+1);
    brid.clear(), brid.resize(0);
    scc.clear(), scc.resize(0);
    inStack.clear(), inStack.resize(n+1);
}
 
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
    root = stnode;
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
    for (int i = 1; i<=n; i++) if (disc[i] == 0) tarjan(i);

    cout<<"Bridges of the graph: "<<nl;
    cout<<brid.size()<<nl;
    for (auto bri : brid) cout<<bri.first<<" "<<bri.second<<nl;

    cout<<"SCC's of the graph: "<<nl;
    cout<<scc.size()<<nl;
    for (int i = 0; i<scc.size(); i++){
        cout<<"SCC #"<<i+1<<" size: "<<scc[i].size()<<nl;
        for (int j = 0; j<scc[i].size(); j++){
            cout<<scc[i][j]<<" ";
        }
        cout<<nl;
    }
    cout<<"Articulation points"<<nl;
    for (int i = 1; i<=n; i++) if (isArt[i] == 1) cout<<i<<" ";
    cout<<nl;
    return 0;
}