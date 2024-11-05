#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(int i=a;i<b;++i)


using namespace std;

const ll maxn = 2e5;
const ll loga = 24;
vector < ll > adj[maxn+5],centree[maxn+5];
ll subt[maxn][loga],dep[maxn][loga],vis[maxn];
ll n,centroids_root;

ll dfsExplore(int anode, int node, int depth, int layer, vector <ll> &elms){
    dep[node][layer] = depth;
    subt[node][layer] = 1;
    elms.pb(node);
    for (auto au : adj[node]){
        if (anode != au && vis[au] == 0){
            subt[node][layer] += dfsExplore(node,au,depth+1,layer,elms);
        }
    }
    return subt[node][layer];
}

bool check(int node, int layer, int tam){
    ll sum = 1;
    for (auto au : adj[node]){
        if (dep[au][layer] > dep[node][layer]){
            sum += subt[au][layer];
            if (subt[au][layer] > tam/2) return false;
        }
    }
    if (tam-sum <= tam/2) return true;
    return false;

}   

void centroidBuild(int centroid_parent, int node, int layer){
    vector <ll> elms;
    ll tam = dfsExplore(node,node,1,layer,elms);
    for(auto elm : elms){
        if (check(elm,layer,tam)){
            vis[elm] = 1;
            if (centroid_parent == -1){
                centroids_root = elm;
            }
            else centree[centroid_parent].pb(elm);
            //cout<<"Centroid layer: "<<layer<<" --> "<<elm<<nl;
            
            for(auto signode : adj[elm]){ //expand to the children.
                if (vis[signode] == 0){
                    centroidBuild(elm,signode,layer+1);
                }
            }
            break;
        }
    }
}

int main(){
    fast;
    cin>>n; 
    fore(i,1,n){ 
        ll x,y;
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    centroidBuild(-1,0,0); //nodes [0, n-1]
}
