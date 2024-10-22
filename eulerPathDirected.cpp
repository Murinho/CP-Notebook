// Tested with: https://cses.fi/problemset/task/1693
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a; i<b; i++)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector <vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second

using namespace std;

const int maxn = 1e5+5;

ll n,m,indeg[maxn],outdeg[maxn];
vi g[maxn],path;

void dfs(int node){
    while(!g[node].empty()){
        int signode = g[node].back();
        g[node].pop_back();
        dfs(signode);
    }
    path.pb(node);
}

// Hierholzer's algorithm
// Directed graph: going from node 1, passing through all edges without repeating and end at node n.
int main(){
    fast;
    cin>>n>>m;
    fore(i,0,m){
        int x,y;
        cin>>x>>y;
        g[x].pb(y);
        outdeg[x]++;
        indeg[y]++;
    }
    bool flag=true;
    fore(i,2,n){
        if (indeg[i] != outdeg[i]){
            flag=false;
            break;
        }
    }
    if (indeg[1]+1 != outdeg[1] || indeg[n]-1 != outdeg[n] || !flag){
        cout<<"IMPOSSIBLE"<<nl;
        return 0;
    }

    dfs(1);

    reverse(ALL(path));
    if (sz(path) != m+1 || path.back() != n){
        cout<<"IMPOSSIBLE"<<nl;
    }
    else{
        for(auto node : path) cout<<node<<" ";
        cout<<nl;
    }
    return 0;
}
