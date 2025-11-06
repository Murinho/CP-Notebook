const ll B = 64; // maximum bit

struct XorBasis{
	vector <ull> xb,src; // change to bitset if handling big numbers
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

void doit(){
	XorBasis xb;

	// to insert:
	xb.insert(a[i],i); // value and index
}