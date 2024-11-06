const ll maxn = 1005;
const ll mod = 1e9+7;
ll c[maxn][maxn];

void pascal(){
    c[0][0] = 1;
    fore(i,1,maxn){
        c[i][0]=c[i][i]=1;
        fore(j,1,i) c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    }
}