#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fast cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
#define nl '\n'

using namespace std;

struct Conn{
    ll a,b,c;
};

ll n,m,q,x,y;
const ll INF = 1e18;
vector <Conn> adj;
vector < vector <ll> > d;

void init(){
    adj.resize(m);
    d.resize(n+1);
    for (int i = 1; i<=n; i++) d[i].assign(n+1,INF);
}

int main(){
    fast;
    cin>>n>>m>>q;
    init();
    for (int i = 0; i<m; i++){
        ll x,y,c;
        cin>>adj[i].a>>adj[i].b>>adj[i].c;
    }
    for (int i = 1; i<=n; i++) d[i][i] = 0;

    for (auto au : adj){
        ll nd = au.a;
        ll nd2 = au.b;
        ll cost = au.c;
        d[nd][nd2] = min(d[nd][nd2], cost);
        d[nd2][nd] = min(d[nd2][nd], cost);
    }

    //Do Floyd-Warshall Algo:
    for (int i = 1; i<=n; i++){
        for (int j= 1; j<=n; j++){
            for (int k = 1; k<=n; k++){
                d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
            }
        }
    } //D[j][k] = shortest distance from j --> k
    while(q--){
        cin>>x>>y;
        if (d[x][y] == INF) cout<<-1<<nl;
        else cout<<d[x][y]<<nl;
    }
    return 0;
}