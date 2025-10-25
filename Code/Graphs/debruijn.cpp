string tour;
int n;
stack<int> s;
vector<int> g[maxn]; // maxn should be greater than 2^n

/*
A de Bruijn sequence of order n on a size-k alphabet A is a cyclic sequence in 
which every possible length-n string on A occurs exactly once as a substring.
*/
void debruijn(){
	cin>>n;
	if (n == 1) {
		cout << "01" << nl;
		return;
	}
	for (int i=0;i<(1ll<<(n-1));i++) {
		g[i].pb((i*2)%(1ll<<(n-1)));
		g[i].pb((i*2+1)%(1ll<<(n-1)));
	}
	s.push(0);
	while (sz(s)) {
		int u = s.top();
		if (sz(g[u])) {
			int v = g[u].back();
			g[u].ppb();
			s.push(v);
		} else {
			tour.pb(u%2+'0');
			s.pop();
		}
	}
	for (int i=0;i<n-2;i++) tour.pb('0');
		
	for (char &u : tour) cout<<u;
	cout << nl;
}