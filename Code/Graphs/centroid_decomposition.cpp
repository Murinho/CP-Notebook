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
    vi elms;
    ll tam = dfsExplore(0,node,1,layer,elms);
    for(auto elm : elms){
        if (check(elm,layer,tam)){
            vis[elm] = 1;
            // Save each node's centroid parent.
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

void doit(){
    // create adjancency list first.
    centroidBuild(-1,1,0); //nodes [1,n]
}
