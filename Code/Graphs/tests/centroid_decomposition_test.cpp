// Tested with: https://codeforces.com/gym/104736/problem/J
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define rofe(i,a,b) for(ll i=a-1;i>=b;--i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define lsbpos(x) __builtin_ffs(x)
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second
#define RB(x) (x<n?r[x]:0)

using namespace std;

const ll maxn = 2e5;
const ll loga = 26;
const ll INF = 1e17;
vi adj[maxn+5],centree[maxn+5];
ll subt[maxn][loga],dep[maxn][loga],vis[maxn],par[maxn][loga],cenpar[maxn],best[maxn],who[maxn],res[maxn];
ll n,centroids_root,q;

void init(){
    fore(i,1,n+1) best[i] = INF, who[i] = INF;
    res[n] = n;
}

ll dfsExplore(ll anode, ll node, ll depth, ll layer, vector <ll> &elms){
    dep[node][layer] = depth;
    if (layer == 0) par[node][0] = anode;
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
    for (auto au : adj[node]){
        if (dep[au][layer] > dep[node][layer]){
            sum += subt[au][layer];
            if (subt[au][layer] > tam/2) return false;
        }
    }
    if (tam-sum <= tam/2) return true;
    return false;
 
}   
 
void centroidBuild(ll centroid_parent, ll node, ll layer){
    vector <ll> elms;
    ll tam = dfsExplore(0,node,1,layer,elms);
    for(auto elm : elms){
        if (check(elm,layer,tam)){
            vis[elm] = 1;
            if (centroid_parent == -1){
                centroids_root = elm;
                cenpar[centroids_root] = 0;
            }
            else cenpar[elm] = centroid_parent; 
            for(auto signode : adj[elm]){ //expand to the children.
                if (vis[signode] == 0){
                    centroidBuild(elm,signode,layer+1);
                }
            }
            break;
        }
    }
}
 

void binaryLift(){
    fore(i,1,loga){
        fore(j,1,n+1){
            par[j][i] = par[par[j][i-1]][i-1];
        }
    }
}

ll lca(ll x, ll y){
    if (x == y) return x;
    if (dep[x][0] > dep[y][0]) swap(x,y); //y es el mas profundo
    ll dif = dep[y][0] - dep[x][0];
    rofe(i,loga,0){
        if (dif & (1ll<<i)) y = par[y][i];
    }
    if (x == y) return x;
    rofe(i,loga,0){
        if (par[x][i] != par[y][i]){
            x = par[x][i];
            y = par[y][i];
        }
    }
    return par[x][0];
}

void update(ll centroid_node, ll &q_node){ //update the centroid tree, updating to the closest painted node.
    if (centroid_node == 0) return;
    ll lcan = lca(centroid_node, q_node);
    ll dist = (dep[centroid_node][0] - dep[lcan][0]) + (dep[q_node][0] - dep[lcan][0]);
    if (best[centroid_node] > dist){
        best[centroid_node] = dist;
        who[centroid_node] = q_node;
    }
    else if (best[centroid_node] == dist){
        who[centroid_node] = min(who[centroid_node], q_node);
    }
    update(cenpar[centroid_node],q_node);
}

pii query(int centroid_node, int q_node){ //first is the ans, second is who
    if (centroid_node == 0) return {INF,INF};
    ll lcan = lca(centroid_node, q_node);
    ll curnode = best[centroid_node] + (dep[centroid_node][0] - dep[lcan][0]) + (dep[q_node][0] - dep[lcan][0]);
    pii p = query(cenpar[centroid_node],q_node);
    if (curnode == p.first){
        ll minic = min(p.second,who[centroid_node]);
        return {curnode,minic};
    }
    else if (curnode < p.first){
        return {curnode,who[centroid_node]};
    }
    else return p;
}


int main(){
    fast;
    cin>>n;
    init();
    fore(i,1,n){
        ll x,y;
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    centroidBuild(-1,1,0);
    binaryLift();
    update(n,n);
    rofe(i,n,1){ //proceed in reverse order.
        pii p = query(i,i);
        res[i] = p.second;
        update(i,i);
    }
    fore(i,1,n+1) cout<<res[i]<<" ";
    cout<<nl;
    return 0;
}