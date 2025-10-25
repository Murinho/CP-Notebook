const ll mod = 1e9+7;
ll tc,n,m,k;

vvi mul(vvi a, vvi b) {
	vvi c(sz(a), vi(sz(b[0])));
	for (int i = 0; i < sz(a); i++) 
		for (int j = 0; j < sz(b); j++)
			for ( int k = 0; k < sz(a); k++) 
				(c[i][j] += a[i][k]*b[k][j]%mod)%=mod; 
	return c;
}

vvi exp( vvi x, ll y) {
	vvi r(sz(x), vi(sz(x)));
	bool flag = false;
	while (y>0){
		if (y&1) {
			if (!flag) r = x, flag = true;
			else r = mul(r,x);
		}
		y=y>>1;
		x = mul(x,x);
	}
	return r;
}

void doit(){
	// define base cases and solve directly.
	// example f(0)=1, f(1)=2, f(2)=3.
	// Function: F(n) = 3*F(n-1) + 2*F(n-2) + F(n-3) + 3.
	mat[0] = {3,2,1,3}; 
	mat[1] = {1,0,0,0}; 
	mat[2] = {0,1,0,0}; 
	mat[3] = {0,0,0,1}; //to keep the +3 constant.
	vi iniv = {3,2,1,1}; //Initial vector.

	mat = exp(mat,k-2); //substract (dims-2) to k.
	ll ans = 0;
	fore(i,0,4){
		ll aux = (mat[0][i]*iniv[i])%mod;
		ans = (ans + aux)%mod;
	}
}