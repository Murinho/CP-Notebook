const ll mod = 998244353;

vi primeEnumerate(int n){
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

void multipleZetaTransform(vi &v){
	const int n = sz(v)-1;
	for(int p : primeEnumerate(n)){
		for (int i = n/p; i; i--){
			v[i] = (v[i]+v[i*p])%mod;
		}
	}
}

void multipleMobiusTransform(vi &v){
	const int n = sz(v)-1;
	for(int p : primeEnumerate(n)){
		for(int i = 1; i*p <= n; i++){
			v[i] = (v[i]-v[i*p]+mod)%mod;
		}
	}
}

// c_k = TotalSum where gcd(i,j)=k of a_i*b_j modulo mod.
vi gcdConvolution(vi a, vi b){
	multipleZetaTransform(a);
	multipleZetaTransform(b);
	fore(i,0,sz(a)) a[i] = (a[i]*b[i])%mod;
	multipleMobiusTransform(a);
	return a;
}

void doit(){
	//insert elements between [1,n].
	// answers [1,n].
}