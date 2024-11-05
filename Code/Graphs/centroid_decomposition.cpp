const ll maxn = 2e5 + 5;
const ll loga = 20;
vi adj[maxn+5],centree[maxn+5];
ll subt[maxn][loga],dep[maxn][loga],vis[maxn];
ll n,centroids_root;

ll dfsExplore(int anode, int node, int depth, int layer, vi &elms){
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
    vi elms;
    ll tam = dfsExplore(node,node,1,layer,elms);
    for(auto elm : elms){
        if (check(elm,layer,tam)){
            vis[elm] = 1;
            if (centroid_parent == -1) centroids_root = elm;
            else centree[centroid_parent].pb(elm);
            for(auto signode : adj[elm]){ //expand to the children.
                if (!vis[signode]) centroidBuild(elm,signode,layer+1);
            }
            break;
        }
    }
}

void doit(){
    // create adjancency list first.
    centroidBuild(-1,0,0); //nodes [0,n-1]
}
