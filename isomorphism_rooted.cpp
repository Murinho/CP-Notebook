//Tested with: https://cses.fi/problemset/task/1700
#include <bits/stdc++.h>
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
 
using namespace std;

const ll maxn = 2e5+100;

map <vector <ll>, ll> mp;
ll tc,idx,n;

void init(){
    mp.clear();
    idx = 1;
}

int dfs(int anode, int node, vector < vector <ll> > &adj){
    vector <ll> v;
    for(auto au : adj[node]){
        if (anode != au) v.pb(dfs(node,au,adj));
    }
    sort(ALL(v));
    if (!mp.count(v)) mp[v] = idx, idx++;
    return mp[v];
}

int main(){
    fast;
    cin>>tc;
    while(tc--){
        cin>>n;
        vector < vector <ll> > adj(n+1),adj2(n+1);
        init();
        fore(i,1,n){
            ll x,y;
            cin>>x>>y;
            adj[x].pb(y);
            adj[y].pb(x);
        }
        fore(i,1,n){
            ll x,y;
            cin>>x>>y;
            adj2[x].pb(y);
            adj2[y].pb(x);
        }
        ll r1 = dfs(1,1,adj);
        ll r2 = dfs(1,1,adj2);
        if (r1 == r2) cout<<"YES"<<nl;
        else cout<<"NO"<<nl;
    }
    return 0;

}   	