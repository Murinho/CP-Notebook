ll z[maxn]; // Finds longest prefix from start and from i
void z_function(string s){
	for (int i = 1, l = 0, r = 0; i < sz(s); ++i) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < sz(s) && s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}