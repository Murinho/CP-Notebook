//Tested with: https://cses.fi/problemset/task/1723/
//Tested with: https://cses.fi/problemset/task/1724/
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

using namespace std;

const ll mod = 1e9+7;
ll tc,n,m,k;
 
vvi mul(vvi a, vvi b) {
    vvi c(sz(a), vi(sz(b[0])));
    for (int i = 0; i < sz(a); i++) 
        for (int j = 0; j < sz(b); j++)
            for ( int k = 0; k < sz(a); k++) 
                (c[i][j] += a[i][k]*b[k][j]%mod)%=mod; //for amount of paths.
                //c[i][j] = min(c[i][j], a[i][k] + b[k][j]); //for shortest path.
    return c;
}
 
 
vvi exp( vvi x, int y) {
    vvi r(sz(x), vi(sz(x),0ll)); //0ll: amount of paths. INF: shortest path
    for ( int i = 0; i < sz(x); i++) r[i][i] = 1; //1ll: amount of paths. 0ll: shortest path.
    while (y>0){
        if (y&1) {
            r = mul(r,x);
        }
        y=y>>1;
        x = mul(x,x);
    }
    return r;
}
 
int main(){
    fast;
    cin>>n>>m>>k;
    vvi adj;
    adj.resize(n,vi(n));
    
    for (int i = 0; i<m; i++){
        ll x,y;
        cin>>x>>y;
        x--, y--;
        adj[x][y]++;
    }
    adj = exp(adj,k);
    cout<<adj[0][n-1]<<nl;
    return 0;
}
