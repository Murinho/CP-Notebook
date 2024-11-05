struct Conn{ ll a,b,c; }; //{node a, node b, cost}
const ll maxn = 1e3+5;
const ll INF = 1e18;
ll n,m,q,d[maxn][maxn];
Conn adj[maxn];

void floyd_warshall(){
    fore(i,0,n+1) fore(j,0,n+1) d[i][j]=INF;
    for (int i = 1; i<=n; i++) d[i][i] = 0;
    for (auto au : adj){ //loop through the edges
        ll nd = au.a;
        ll nd2 = au.b;
        ll cost = au.c;
        d[nd][nd2] = min(d[nd][nd2], cost);
        d[nd2][nd] = min(d[nd2][nd], cost);
    }

    fore(i,1,n+1){
        fore(j,1,n+1){
            fore(k,1,n+1){
                d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
            }
        }
    } //D[j][k] = shortest distance from j --> k
}