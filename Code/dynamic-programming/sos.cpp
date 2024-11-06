const ll maxbit = 20;
const ll maxn = 1<<20;
ll dp[maxn][maxbit+1]; //{mask,last bit}
ll n,sos[maxn],a[maxn];

void sum_over_subsets(){
    fore(mask,0,maxn){
		dp[mask][0] = a[mask];
		fore(x,0,maxbit){
			dp[mask][x+1] = dp[mask][x];
			if (mask & (1<<x)){
				dp[mask][x+1] += dp[mask - (1ll<<x)][x];
			}
		}
		sos[mask] = dp[mask][maxbit];
	}
}