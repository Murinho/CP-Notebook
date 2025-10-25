const ll maxn = 2e5+500;
const ll INF = 1e18;
const ll loga = 22;
ll n,k,sp[maxn][loga],a[maxn];

ll query(int l, int r){
	//Check in steps of powers of 2.
	int tam = (r-l+1);
	ll res = INF;
	rofe(i,loga,0){
		if (tam & (1ll<<i)){
			res = min(res,sp[l][i]);
			l += (1ll<<i);
		}
	}
	return res;
}

void build(){ // Minimums sparse table.
	fore(i,1,n+1) sp[i][0]=a[i];
	fore(i,1,loga){
		fore(j,1,n+1){
			if (j + (1ll<<i) - 1 <= n){ // 
				sp[j][i] = min(sp[j][i-1], sp[j + (1ll<<(i-1))][i-1]);
			}
		}
	}
}
