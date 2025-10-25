const ll maxn = 1e6+5;
ll lp[maxn];
vi primes;

void sieve_linear(){
	fore(i,2,maxn){
		if (!lp[i]){
			lp[i]=i;
			primes.pb(i);
		}
		for (int j=0; j < sz(primes) && pr[j]<=lp[i] && i*pr[j]<maxn; j++) {
			lp[i * pr[j]] = pr[j];
		}
	}
}
