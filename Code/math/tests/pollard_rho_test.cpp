// Tested with AC: https://www.spoj.com/problems/FACT0/
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define rofe(i,a,b) for(ll i=a-1;i>=b;--i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define lsbpos(x) __builtin_ffs(x)
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second
#define eb emplace_back
#define ppb pop_back
#define i128 __int128_t
#define ull unsigned long long
 
using namespace std;

using u64 = uint64_t;
using u128 = __uint128_t;

static std::mt19937_64 rng((uint64_t)chrono::steady_clock::now().time_since_epoch().count());

static inline u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

static inline bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

static inline bool is_prime(u64 n) { // returns true if n is probably prime, else returns false.
    if (n < 2) return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (check_composite(n, a, d, r)) return false;
    }
    return true;
}

static inline ll mult(ll &a, ll &b, ll &mod){
	return (i128)a*b % mod;
}

static inline ll f(ll x, ll &c, ll mod){
	return (mult(x, x, mod) + c) % mod;
}

static inline ll rho(ll &n, ll &x0, ll &c){
	ll x = x0;
	ll y = x0;
	ll g = 1;
	while(g == 1){
		x = f(x,c,n); // tortoise
		y = f(y,c,n); // hare
		y = f(y,c,n);
		g = __gcd(abs(x-y), n);
	}
	return g;
}

static inline ll do_rho(ll n){
    if ((n & 1LL) == 0) return 2;

    while (true) {
        ll x0 = (ll)(rng() % (n - 2)) + 2;  // [2, n-1]
        ll c  = (ll)(rng() % (n - 1)) + 1;  // [1, n-1]

        ll d = rho(n, x0, c);
        if (d != n) return d;
        // else retry with new random parameters
    }
}

vi primes;

static inline void factorize(ll n){
    if (n == 1) return;

    while ((n & 1LL) == 0) {
        primes.eb(2);
        n >>= 1;
    }
    if (n == 1) return;

    for (ll p = 3; p * p <= n && p <= 1e5; p += 2) { 
        while (n % p == 0) {
            primes.eb(p);
            n /= p;
        }
    }
    if (n == 1) return;

    // Now n is either prime or has only "large" factors
    if (is_prime(n)) {
        primes.eb(n);
        return;
    }

    ll d = do_rho(n);
    factorize(d);
    factorize(n / d);
}


void init(){
	primes.clear();
	primes.reserve(64);
}

void solve(ll &n){
	init();
	factorize(n);
	
	sort(ALL(primes));
	
	int cnt=1;
	fore(i,1,sz(primes)){
		if (primes[i-1] != primes[i]){
			cout << primes[i-1] << "^" << cnt << " ";
			cnt = 0;
		}
		cnt++;
	}
	
	cout << primes.back() << "^" << cnt << nl;
	return;
}

int main(){
    fast;
    srand(time(0));
    ll n;
    while(1){
    		
    		cin >> n;
    		if (n == 0) break;
        	solve(n);
    }
    return 0;
}