struct XorBasis {
	static constexpr int B = 64;
    array<ull, B> basis{}; // numeric basis
    array<vector<ull>, B> coef{}; // provenance bitsets (chunked 64-bit blocks)
    int rank_ = 0;
    ll added_cnt = 0; // # inserted so far
    int chunks = 0; // # of 64-bit blocks in provenance bitsets
 
    // Ensure provenance bitsets have capacity for index idx
    void ensure_capacity(ll idx) {
        int need_chunks = int(idx / B) + 1;
        while (chunks < need_chunks) {
        	fore(b,0,B) if (!coef[b].empty()) coef[b].pb(0ULL);
            chunks++;
        }
    }
 
    // Create a provenance bitset with only bit 'idx' set
    vector<ull> singleton_mask(ll idx) {
        ensure_capacity(idx);
        vector<ull> m(chunks, 0ULL);
        m[idx / B] |= (1ULL << (idx % B));
        return m;
    }
 
    // XOR two provenance bitsets into a (resize a if needed)
    static void xor_into(vector<ull>& a, const vector<ull>& b) {
        if (!sz(b)) return;
        if (sz(a) < sz(b)) a.resize(sz(b), 0ULL);
        fore(i,0,sz(b)) a[i] ^= b[i];
    }
 
    // Insert x with its original 0-based index idx. Returns true if rank increased.
    bool add(ull x, long long idx) {
        ensure_capacity(idx);
        ++added_cnt;
 
        vector<ull> cur = singleton_mask(idx); // provenance for this x
 
        for (int b = B - 1; b >= 0; --b) {
            if (!((x >> b) & 1ULL)) continue;
            if (!basis[b]) {
                basis[b] = x;
                // store provenance (ensure exact size)
                if (sz(cur) < chunks) cur.resize(chunks, 0ULL);
                coef[b] = move(cur);
                ++rank_;
                return true;
            }
            x ^= basis[b];
            xor_into(cur, coef[b]);
        }
        return false; // dependent
    }
 
    // Standard reduce
    ull reduce(ull x) const {
        for (int b = B - 1; b >= 0; --b)
            if (basis[b] && ((x >> b) & 1ULL)) x ^= basis[b];
        return x;
    }
 
    bool can_represent(ull x) const { return reduce(x) == 0ULL; }
    int rank() const { return rank_; }
    int get_added_cnt() const { return (int)added_cnt; }
 
    // How many distinct XORs exist
    ull get_distinct_xor_subsequences() const { return (1ULL << rank_); }
    
    ll get_xor_target_subsequences_amount(ll x){ // How many subsequences map to a given XOR value
    	if (!can_represent(x)) return 0;
    	return (1ll<<(ll)(added_cnt - rank())); // POTENTIAL OVERFLOW, you may use Binary Expo.
    }
    
    // Return the basis vectors in reduced row-echelon form (unique leading bits, zero above).
    vector<ull> to_vector_rref() const {
        array<ull, B> r = basis;
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
 
    // For a given representable target x, return one subset of original indices producing x.
    // Returns empty vector if x is not representable.
    vi reconstruct(ull x) const {
        vector<ull> acc; // accumulated provenance
        for (int b = B - 1; b >= 0; --b) {
            if (basis[b] && ((x >> b) & 1ULL)) {
                x ^= basis[b];
                xor_into(acc, coef[b]);
            }
        }
        if (x != 0ULL) return {}; // not representable
 
        // Extract indices from acc bitset
        vi indices;
        fore(block,0,sz(acc)){
        	ull w = acc[block];
            while (w) {
                int t = __builtin_ctzll(w);
                indices.pb(block * 64 + t); // 0-based index
                w &= (w - 1);
            }
        }
        return indices;
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