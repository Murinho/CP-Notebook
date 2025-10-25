const ll mod = 998244353;

void subsetZetaTransform(vi &v){
	int n = sz(v); // n must be a power of 2.
	for(int j = 1; j<n; j <<= 1){
		fore(i,0,n){
			if (i&j) v[i] += v[i^j], v[i] %= mod;
		}
	}
}

void subsetMobiusTransform(vi &v){
	int n = sz(v); // n must be a power of 2.
	for(int j = 1; j<n; j <<= 1){
		fore(i,0,n){
			if (i&j) v[i] -= v[i^j], v[i] += mod, v[i] %= mod;
		}
	}
}

// c_k = Total sum where (i,j), i|j = k of a_i*b_j
vi orConvolution(vi a, vi b){
	subsetZetaTransform(a);
	subsetZetaTransform(b);
	fore(i,0,sz(a)) a[i] *= b[i], a[i] %= mod;
	subsetMobiusTransform(a);
	return a;
}

void doit(){
	// read a and b arrays.
	// get the answer vector
	// print answers % mod.
}