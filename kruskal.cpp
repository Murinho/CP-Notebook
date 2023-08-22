#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

///Minimum Spanning Tree with Kruskal's Algorithm.

int n,k,a,b,c,edges = 0,totalw = 0;
const int maxn = 1e5+5;
vector < pair < int, pair <int, int> > > adj; ///Cost, Node1, Node2.
map <int, vector < pair <int, int> > > mst; ///Node1, Node2, Cost.

struct UnionFind{
    int ran,pad,tam;
};
UnionFind UF[maxn];

int bus(int u)
{
	if (UF[u].pad!=u){
        UF[u].pad=bus(UF[u].pad);
	}
	return UF[u].pad;
}
void unir(int u ,int v)
{
	u=bus(u); v=bus(v);
	if (u==v) return; ///Si tienen el mismo padre.
	if (UF[u].ran>UF[v].ran){
        UF[v].pad=u;
        UF[u].tam+=UF[v].tam;
    }
	else if (UF[u].ran<UF[v].ran) {
        UF[u].pad=v;
        UF[v].tam+=UF[u].tam;
    }
	else {
        UF[u].pad=v;
        UF[v].ran++;
        UF[v].tam+=UF[u].tam;
    }
	return;
}


int main()
{
    cin>>n>>k; ///Number of nodes, number of edges. Strictly k+1>=n (graph completely connected).
    for (int i=0 ;i<=n; i++){
        UF[i].ran=0;
        UF[i].pad=i;
        UF[i].tam=1;
    }
    for (int i = 0; i<k; i++){
        cin>>a>>b>>c;
        if (a > b) swap(a,b);
        adj.pb({c,{a,b}});
    }
    sort(adj.begin(),adj.end());
    edges = 0;
    totalw = 0;
    for (int i = 0; i<k && edges<n; i++){
        a = adj[i].second.first;
        b = adj[i].second.second;
        if (bus(a) != bus(b)){
            cout<<"Join: "<<adj[i].second.first<<" "<<adj[i].second.second<<". Cost: "<<adj[i].first<<endl;
            ///Unir.
            unir(a,b);
            edges++;
            //cout<<adj[i].first<<endl;
            totalw += adj[i].first;
            mst[a].pb({b,adj[i].first});
            mst[b].pb({a,adj[i].first});
        }
    }
    cout<<"Total weight of MST: "<<totalw<<endl;
    return 0;
    cout<<"Adjacency list by node of the MST \n";
    for (int i = 1; i<=n; i++){
        cout<<i<<" : ["<<mst[i].size()<<"] --> ";
        for (int j = 0; j<mst[i].size(); j++){
            cout<<mst[i][j].first<<" ";
        }
        cout<<endl;
    }

}
