const ll mod = 998244353;

vi primeEnumerate(int n){ //Linear sieve.
	vi p;
	vector <bool> b(n+1,1);
	fore(i,2,n+1){
		if (b[i]) p.pb(i);
		for(int j : p){
			if (i*j>n) break;
			b[i*j]=0;
			if (i%j == 0) break;
		}
	}
	return p;
}

void divisorZetaTransform(vi &v){
	const int n = sz(v)-1;
	for(int p : primeEnumerate(n)){
		for (int i = 1; i*p <= n; i++){
			v[i*p] = (v[i*p]+v[i])%mod;
		}
	}
}

void divisorMobiusTransform(vi &v){
	const int n = sz(v)-1;
	for(int p : primeEnumerate(n)){
		for(int i = n/p; i; i--){
			v[i*p] = (v[i*p]-v[i]+mod)%mod;
		}
	}
}

// c_k = TotalSum where lcm(i,j)=k of a_i*b_j modulo mod.
vi lcmConvolution(vi a, vi b){
	divisorZetaTransform(a);
	divisorZetaTransform(b);
	fore(i,0,sz(a)) a[i] = (a[i]*b[i])%mod;
	divisorMobiusTransform(a);
	return a;
}

void doit(){
	//insert elements between [1,n].
	// answers [1,n].
}