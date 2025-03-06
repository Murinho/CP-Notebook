const ll maxn = 2e5+5;
const ll loga = 20;
vi adj[maxn+5];
ll subt[maxn][loga],dep[maxn][loga],vis[maxn],cenpar[maxn];
ll n,centroids_root;

ll dfsExplore(ll anode, ll node, ll depth, ll layer, vi &elms){
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
 
bool check(ll node, ll layer, ll tam){
    ll sum = 1;
    for (auto &au : adj[node]){
        if (dep[au][layer] > dep[node][layer]){
            sum += subt[au][layer];
            if (subt[au][layer] > tam/2) return false;
        }
    }
    if (tam-sum <= tam/2) return true;
    return false;
}   
 
void centroidBuild(ll centroid_parent, ll node, ll layer){
    vi elms;
    ll tam = dfsExplore(0,node,1,layer,elms); // change anode to -1 if nodes [0,n-1]
    for(auto &elm : elms){
        if (check(elm,layer,tam)){
            vis[elm] = 1;
            // Save each node's centroid parent.
            if (centroid_parent == -1){
                centroids_root = elm;
            }
            cenpar[elm] = centroid_parent; 
            for(auto &signode : adj[elm]){ //expand to the children.
                if (vis[signode] == 0){
                    centroidBuild(elm,signode,layer+1);
                }
            }
            break;
        }
    }
}

void doit(){
    // create adjancency list first.
    centroidBuild(-1,1,0); //nodes [1,n]
}
