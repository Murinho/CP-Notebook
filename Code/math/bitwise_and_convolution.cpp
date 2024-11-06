const ll mod = 998244353;

void supersetZetaTransform(vi &v){
    int n = sz(v); // n must be a power of 2.
    for(int j = 1; j<n; j <<= 1){
        fore(i,0,n){
            if (i&j) v[i^j] += v[i], v[i^j] %= mod;
        }
    }
}

void supersetMobiusTransform(vi &v){
    int n = sz(v); // n must be a power of 2.
    for(int j = 1; j<n; j <<= 1){
        fore(i,0,n){
            if (i&j) v[i^j] -= v[i], v[i^j] += mod, v[i^j] %= mod;
        }
    }
}
// c_k = Total sum where (i,j), i&j = k of a_i*b_j
vi andConvolution(vi a, vi b){
    supersetZetaTransform(a);
    supersetZetaTransform(b);
    fore(i,0,sz(a)) a[i] *= b[i], a[i] %= mod;
    supersetMobiusTransform(a);
    return a;
}

void doit(){
    n = 1<<n;
    // Then read values of a and b arrays.
    // get the answer vector.
    // apply modulo when printing answers.
}