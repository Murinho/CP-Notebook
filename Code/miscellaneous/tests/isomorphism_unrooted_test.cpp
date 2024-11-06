//Tested with: https://cses.fi/problemset/task/1701/
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
 
vector<ll> center(int n, vector< vector <ll> > &adj) {
    int deg[n+1] = {0};
    vector<ll> v;
    for (int i = 1; i <= n; i++) {
        deg[i] = sz(adj[i]);
        if (deg[i] == 1)
            v.pb(i), deg[i]--;
    }
    int m = sz(v);
    while(m < n) {
        vector<ll> vv;
        for (auto i: v) {
            for (auto j: adj[i]) {
                deg[j]--;
                if (deg[j] == 1)
                    vv.pb(j);
            }
        }
        m += sz(vv);
        v = vv;
    }
    return v;
}
map<vector<ll>, ll> mp;
int idx = 0;
 
int dfs(int s, int p, vector< vector <ll> > &adj) {
    vector<ll> v;
    for (auto i: adj[s]) {
        if (i != p) 
            v.push_back(dfs(i, s, adj));
    }
    sort(ALL(v));
    if (!mp.count(v)) mp[v] = idx++;
    return mp[v];
}
int main(){
    fast;
    ll tc,n;
    cin>>tc;
    while(tc--){
        cin>>n;
        ll x,y;
        vector < vector <ll> > adj(n+1), adj2(n+1);
 
        fore(i,1,n){
            cin>>x>>y;
            adj[x].pb(y);
            adj[y].pb(x);
        }
        fore(i,1,n){
            cin>>x>>y;
            adj2[x].pb(y);
            adj2[y].pb(x);
        }
        vector <ll> v1 = center(n,adj), v2 = center(n,adj2);
 
        bool flag = false;
        int s1 = dfs(v1[0], -1, adj);
        for(auto s : v2){
            int s2 = dfs(s, -1, adj2);
            if (s1 == s2){
                flag=true;
                break;
            }
        }
        cout<<(flag ? "YES" : "NO")<<nl;
    }
    return 0;
}