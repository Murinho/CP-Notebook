const ll maxn = 2e5+5;
const ll loga = 20;
ll n,up[maxn][loga],dep[maxn];

void binlift(){ 
    // Assuming we have all direct parents for each node (up[node][0])
    fore(i,1,loga){
        fore(j,1,n+1) up[j][i] = up[up[j][i-1]][i-1];
    }
}

ll lca(ll x, ll y){ //calculate the depths of each node before.
    if (dep[x] < dep[y]) swap(x,y);
    ll dif = dep[x]-dep[y];
    rofe(i,loga,0){
        if (dif & (1ll<<i)) x = up[x][i];
    }
    if (x == y) return x;
    rofe(i,loga,0){
        if (up[x][i] != up[y][i]){
            x = up[x][i];
            y = up[y][i];
        }
    }
    return up[x][0];
}