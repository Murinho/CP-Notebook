const int mod = 998244353;

int inverse(int x, int mod) {
	return x == 1 ? 1 : mod - mod / x * inverse(mod % x, mod) % mod;
}

void xormul(vi a, vi b, vi &c){
	int m = sz(a);
	c.resize(m);
	for (int n = m / 2; n > 0; n /= 2)
		for (int i = 0; i < m; i += 2 * n)
			for (int j = 0; j < n; j++) {
				int x = a[i + j], y = a[i + j + n];
				a[i + j] = (x + y) % mod;
				a[i + j + n] = (x - y + mod) % mod;
			}
	for (int n = m / 2; n > 0; n /= 2)
		for (int i = 0; i < m; i += 2 * n)
			for (int j = 0; j < n; j++) {
				int x = b[i + j], y = b[i + j + n];
				b[i + j] = (x + y) % mod;
				b[i + j + n] = (x - y + mod) % mod;
			}
	fore(i,0,m) c[i] = a[i] * b[i] % mod;
	for (int n = 1; n < m; n *= 2)
		for (int i = 0; i < m; i += 2 * n)
			for (int j = 0; j < n; j++) {
				int x = c[i + j], y = c[i + j + n];
				c[i + j] = (x + y) % mod;
				c[i + j + n] = (x - y + mod) % mod;
			}
	int mrev = inverse(m, mod);
	fore(i,0,m) c[i] = c[i] * mrev % mod;
}

// Given two arrays of size 2^N, find:
// c_k = Total_Sum of (i,j) where (i [XOR] j) == k, a_i*b_j

void doit(){
	int n;
	vi a(1<<n),b(1<<n),c; //c is answer vector of size (1<<n).
}