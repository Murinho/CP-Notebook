vector <int> phi;

//Amount of coprime numbers (gcd(a,b) == 1) for each number in (1 <= i <= n).
//counting the number of integers between 1 and i, which are coprime to i.
void euler_totient(int n) { 
	phi.resize(n+1);
	for (int i = 0; i <= n; i++) phi[i] = i;

	for (int i = 2; i <= n; i++) {
		if (phi[i] == i) {
			for (int j = i; j <= n; j += i)
				phi[j] -= phi[j] / i;
		}
	}
}

//Amount of numbers 0 <= i < m such that gcd(a+i,m) == gcd(a,m)
int phiFunc(int a, int m) { 
	ll y = m/__gcd(a,m);
	ll ans = y;
	for(ll i = 2; i*i<=m; i++){
		if (y%i == 0){
			ans -= ans/i;
			while(y%i == 0) y /= i;
		}
	}
	if (y>1) ans -= ans/y;
	return ans;
}