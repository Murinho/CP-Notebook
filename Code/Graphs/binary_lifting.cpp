#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

const int LOG = 18;
const int maxn = 2e5 + 5;
vector <int> children[maxn];
int up[maxn][LOG]; //up[v][j] is a 2^th ancestor of v.
int depth[maxn];

void parenting(int a){
    for (int b : children[a]){
        depth[b] = depth[a] + 1;
        up[b][0] = a; //a is parent of b
        for (int j = 1; j<LOG; j++){
            up[b][j] = up[up[b][j-1]][j-1];
        }
        parenting(b);
    }
}

int get_lca(int a, int b){ //Made in O(logN)
    if (depth[a] < depth[b]){
        swap(a,b);
    }
    int k = depth[a] - depth[b];
    
    for (int j = LOG-1; j>=0; j--){
        if (k & (1<<j)){
            a = up[a][j];
        }
    }    

    if (a == b){
        return a;
    }
    for (int j = LOG-1; j>=0; j--){
        if (up[a][j] != up[b][j]){
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

int main()
{
    int n,node,node2,m,sohn,q;
    cin>>n; ///Given n nodes, and n-1 edges.
    for (int i = 1; i<n; i++){
        int a,b;
        cin>>a>>b; //a is parent of b:
        children[a].pb(b);
    }
    parenting(1); //Empezar en el indice del nodo raíz del arbol.
    cin>>q;
    while(q--){
        cin>>node>>node2;
        cout<<get_lca(node,node2)<<"\n";
    }
    
}