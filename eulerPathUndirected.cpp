// Tested with: https://cses.fi/problemset/task/1691
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
const int maxm = 2e5+5;

ll seen[maxm],n,m;
vector<int> path;
vector < pii > g[maxn];

void dfs(int node){
    while(!g[node].empty()){
        auto [signode, idx] = g[node].back();
        g[node].pop_back();
        if (seen[idx]) continue;
        seen[idx]=true;
        dfs(signode);
    }
    path.pb(node);
}

// Hierholzer's algorithm
// Going from node 1, passing through all edges without repeating and come back to node 1.
int main(){
    fast;
    cin>>n>>m;
    fore(i,0,m){
        int x,y;
        cin>>x>>y;
        x--, y--;
        g[x].pb({y,i}), g[y].pb({x,i});
    }
    fore(i,0,n){
        if (sz(g[i])%2){
            cout<<"IMPOSSIBLE"<<nl;
            return 0;
        }
    }

    dfs(0);

    if (sz(path) != m+1){
        cout<<"IMPOSSIBLE"<<nl;
    }
    else{
        for(auto node : path) cout<<node+1<<" ";
        cout<<nl;
    }
    return 0;
}