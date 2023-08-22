#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

int n,a,b,logar,q;
vector <vector <int> > up;
vector <int> parent,depth;

int getKthAncestor(int node, int k){
    if (depth[node] < k){
        return -1;
    }
    for (int j = 0; j<logar; j++){
        if ( k & (1 << j)){
            node = up[node][j];
        }
    }
    return node;
}

void clean(){
    parent.resize(n+1);
    depth.resize(n+1);
    up.resize(n+1);
}

int main()
{
    int node, k;
    cin>>n; ///Given n nodes, and n-1 edges, assuming there are no cycles.
    clean();
    for (int i = 1; i<n; i++){
        cin>>a>>b; ///A is parent of B.
        parent[b] = a;
    }
    ///Precalculate the ancestors by powers of 2.
    logar = 0;
    while ((1 << logar) <= n){
        logar++;
    }
    parent[1] = 1;
    for (int v = 1; v<=n; v++){
        up[v].pb(parent[v]);
        if (v != 1){
            depth[v] = depth [parent[v]] + 1;
        }
        for (int j = 1; j<logar; j++){
            //cout<<v<<" "<<j<<endl;
            up[v].pb(up[up[v][j-1]][j-1]);
        }
    }
    cin>>q; ///Queries.
    while (q--){
        cin>>node>>k; ///Given a node, answer what is his k'th ancestor
        cout<<getKthAncestor(node,k)<<endl;
    }
}

/*
7
0 1
1 3
1 4
3 6
0 2
2 5
*/
