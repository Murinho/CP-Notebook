vi kmp(string s){
	vi vs(sz(s));
	fore(i,1,sz(s)){
		int j = vs[i-1];
		while(j!=0 && s[i] != s[j]){
			j = vs[j-1];
		}
		if(s[i] == s[j]) j++;
		vs[i] = j;
	}
	return vs;
}

void doit(){
	string s,t,p;
	cin>>s; // main text.
	cin>>t; // target.
	p = t, p += "#", p += s;;
	vi res = kmp(p);
	ll ans = 0;
	for (auto au : res){
		if (au == sz(t)) ans++;
	}
}