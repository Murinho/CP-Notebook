//Tested with: https://cses.fi/problemset/task/1139/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((int)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second
 
using namespace __gnu_pbds;
using namespace std;
 
const ll maxn = 2e5+5;
 
ll n;
vi adj[maxn];
set <ll> colors[maxn];
ll res[maxn];
 
void dfs(int anode, int node){
    for(auto au : adj[node]){
        if (anode != au){
            dfs(node,au);
            if (sz(colors[node]) < sz(colors[au])){ //current node should always be the larger.
                swap(colors[node],colors[au]);
            }
            for(auto elm : colors[au]) colors[node].insert(elm); //small to large.
        }
    }
    res[node] = sz(colors[node]);
}
 
 
 
int main(){
    fast;
    cin>>n;
    fore(i,1,n+1){
        ll x;
        cin>>x;
        colors[i].insert(x);
    }
    fore(i,1,n){
        ll x,y;
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs(1,1);
    fore(i,1,n+1) cout<<res[i]<<" ";
    cout<<nl;
    return 0;
}