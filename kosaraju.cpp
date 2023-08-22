#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

int n,k,a,b,cont = 1,topic,sizic,maxscc = 0;
map <int, vector <int> >adj,trans,scc;
map <int, pair <int, int> > order;
map <int, bool> vis;
stack <int> stk;


void dfs(int node){
    vis[node] = true;
    order[node].first = cont;
    cont++;
    for (int i = 0; i<adj[node].size(); i++){
        int signode = adj[node][i];
        if (!vis[signode]){
            dfs(signode);
        }
    }
    order[node].second = cont;
    cont++;
    stk.push(node);
}

void dfs2(int node){
    scc[sizic].pb(node);
    vis[node] = true;
    for (int i = 0; i<trans[node].size(); i++){
        int signode = trans[node][i];
        if (!vis[signode]){
            dfs2(signode);
        }
    }
}

int main()
{
    //PARA GRAFICAS DIRIGIDAS.
    
    cin>>n>>k; ///Amount of nodes and edges.
    for (int i = 0; i<k; i++){
        cin>>a>>b; ///a --> b
        adj[a].pb(b);  ///Real graph
        trans[b].pb(a); ///Transpose graph
    }
    for (int i = 0; i<=n; i++){
        if (!vis[i]) dfs(i);
    }
    for (int i = 0; i<=n; i++){
        cout<<i<<": "<<order[i].first<<" "<<order[i].second<<endl;
    }
    vis.clear();
    sizic = 0;
    while (!stk.empty()){
        topic = stk.top();
        stk.pop();
        if (!vis[topic]){
            sizic++;
            dfs2(topic);
        }
    }
    cout<<sizic<<endl;
    for (int i = 1; i<=sizic; i++){
        cout<<"SCC: "<<i<<endl;
        int tam = scc[i].size();
        maxscc = max(maxscc,tam);
        for (int j = 0; j<tam; j++){
            cout<<scc[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Biggest SCC: "<<maxscc<<endl;
}

/*
8 10
0 1
1 2
2 3
3 0
2 4
4 5
5 6
6 4
7 6
7 8
*/
