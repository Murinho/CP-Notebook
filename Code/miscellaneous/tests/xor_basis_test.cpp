// Tested with AC: https://codeforces.com/gym/105974/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
 
using namespace __gnu_pbds;
using namespace std;

const ll B = 64;
const ll maxn = 1e5+100;

struct XorBasis{
	vector <ull> xb,src;
	ll rank, added_cnt;
	vi p;
	
	XorBasis(): xb(B), src(B), rank(0), added_cnt(0) {}
	
	bool insert(ull x, ll idx) {
		added_cnt++;
		
		ll mrk = 1ll << rank;

	    for(int i = B - 1; i >= 0; i --) {
	        if((x >> i) & 1) {
	            if(!xb[i]) {
	                xb[i] = x;
	                src[i] = mrk;
	                p.pb(idx);
	                rank++;
	                return true;
	            }else {
	                x ^= xb[i];    
	                mrk ^= src[i];
	            }
	        }
	    }
	    return false;
	}
	 
	ll can_represent(ll x){ // returns -1 if x is not representable, else the mask with the source indices to form x.
	    ll ret = 0;
	    for(int i = B - 1; i >= 0; i --) {
	        if((x >> i) & 1) {
	            if(!xb[i]) return -1;
	            ret ^= src[i];
	            x ^= xb[i];
	        }
	    }
	    return ret;
	}
	
	vi reconstruct(ll x){
		ll y = can_represent(x);
		if(y == -1) return {}; // not possible to represent
		
		vi ret;
		fore(i,0,B){
			if ((y >> i) & 1) ret.pb(p[i]);
		}
		
		return ret;
	}
	
	ll get_rank() { return rank; }
	ll get_added_cnt(){ return added_cnt; }
	
	ll get_distinct_xor_subsequences() const { return (1ll << rank); }
	
	ll get_xor_target_subsequences_amount(ll x){ // How many subsequences map to a given XOR value
    	if (can_represent(x) == -1) return 0;
    	return (1ll<<(ll)(added_cnt - rank)); // POTENTIAL OVERFLOW, you may use Binary Expo.
    }
    
    vector<ull> to_vector_rref() const {
        vector <ull> r = xb;
        // Make upper-triangular vectors also eliminate upwards to get RREF-ish set
        for (int i = B - 1; i >= 0; --i) if (r[i]) {
            for (int j = i - 1; j >= 0; --j) if (r[j] && ((r[i] >> j) & 1ULL)) {
                r[i] ^= r[j];
            }
        }
        vector<ull> out;
        for (int b = 0; b < B; ++b) if (r[b]) out.pb(r[b]);
        return out;
    }
    
    ll get_kth_smallest_xor_value(ll k){ // k must be 0-indexed
		ll dxs = get_distinct_xor_subsequences();
    	if (k < 0 || k >= dxs) return -1;
    	
    	auto xb = to_vector_rref();
    	
    	sort(ALL(xb));
    	
    	ll ret = 0;
    	
    	for(ll i = sz(xb)-1; i>=0; i--){
    		ll pot = (1ll<<i);
    		if (pot <= k){
    			k -= pot;
    			ret ^= xb[i];
    		}
    	}
    	return ret;
    }
    
    ll get_kth_largest_xor_value(ll k){ // k must be 0-indexed
    	return get_kth_smallest_xor_value(get_distinct_xor_subsequences() - k - 1);
    }
};

ll a[maxn];

int main(){
    fast;
    ll n,q;
    cin >> n;
    XorBasis xb;
    fore(i,0,n){
    	cin >> a[i];
    	xb.insert(a[i],i);
    }
    cin >> q;
    fore(i,0,q){
    	ll x;
    	cin >> x;
    	vi ret = xb.reconstruct(x);
    	int pos = 0;
    	fore(j,0,n){
    		if (pos < sz(ret) && ret[pos] == j) cout << 1, pos++;
    		else cout << 0;
    	}
    	cout << nl;
    }
    return 0;
}