// Longest increasing subsequence O(nlogn)
const ll INF = 1e18;
int lis(const vi &a) {
	int n = sz(a);
	vi d(n+1, INF);
	d[0] = -INF;

	for (int i = 0; i < n; i++) {
		int j = upper_bound(ALL(d), a[i]) - d.begin();
		if (d[j-1] < a[i] && a[i] < d[j]) d[j] = a[i];
	}

	int ans = 0;
	fore(i,0,n+1) if (d[i]<INF) ans = i;
	return ans;
}