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
 
vvi exp( vvi x, int y) { // matrix and desired power.
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

void doit(){
    // build adjacency (or costs) matrix of size(n*n).
    // after exponentiating mat[i][j] denotes the path from i to j.
}