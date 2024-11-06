// Tested with: https://judge.yosupo.jp/problem/bitwise_xor_convolution
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a; i<b; i++)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector <vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second
#define RB(x) (x<n?r[x]:0)

using namespace std;

const int mod = 998244353;

int inverse(int x, int mod) {
	return x == 1 ? 1 : mod - mod / x * inverse(mod % x, mod) % mod;
}

void xormul(vi a, vi b, vi &c) {
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

int main(){
	fast;
	int n; cin >> n;
    vi a(1<<n),b(1<<n),c;
	for (int i = 0; i < (1 << n); i++) cin>>a[i];
	for (int i = 0; i < (1 << n); i++) cin>>b[i];
	xormul(a, b, c);
	for (int i = 0; i < (1 << n); i++) cout <<c[i]<<" ";
    cout<<nl;
    return 0;
}