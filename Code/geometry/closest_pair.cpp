ll closestPair(vector <pii> pts){ 
    //Calcula el par de puntos en 2D mas cercanos entre si, retorna su distancia euclidiana.
	int n = sz(pts);
    sort(ALL(pts));
    set<pii> s;

	ll ans = INF;
    int pos = 0;
    fore(i,0,n){
        ll d = ceil(sqrt(ans));
        while (pts[i].first - pts[pos].first >= d) {
            s.erase({pts[pos].second, pts[pos].first});
            pos++;
        }

        auto it1 = s.lower_bound({pts[i].second - d, pts[i].first});
        auto it2 = s.upper_bound({pts[i].second + d, pts[i].first});
        
        for (auto it = it1; it != it2; it++) {
            ll dx = pts[i].first - it->second;
            ll dy = pts[i].second - it->first;
			if (ans > 1LL * dx * dx + 1LL * dy * dy){
				ans = 1LL * dx * dx + 1LL * dy * dy;
			} 
        } 
        s.insert({pts[i].second, pts[i].first}); 
    }
	return ans;
}
