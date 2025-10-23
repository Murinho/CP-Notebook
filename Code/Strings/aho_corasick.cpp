const int MAXN = 1e6+10;
map<char, int> to[MAXN]; // if TLE change to array
string a[MAXN];
int lnk[MAXN],sz=1;
ll que[MAXN],endlink[MAXN]; 
vi leaf[MAXN],ans[MAXN];
void add_str(string s, int id) {
	int v = 0;
	for(char c: s) {
		if(!to[v].count(c)) to[v][c] = sz++;
		v = to[v][c];
	}
	leaf[v].pb(id); //Node in automata where a word ends
}
void push_links() {
	queue<int> q({0});
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(auto [c,u]: to[v]){
			int j = lnk[v];
			while(j && !to[j].count(c)) j=lnk[j];
			if(to[j].count(c) && to[j][c]!=u) lnk[u] = to[j][c];
			endlink[u] = leaf[lnk[u]].size()>0?lnk[u]:endlink[lnk[u]];
			q.push(u);
		}
	}
}
void walk(string s){ //KMP with multiple target patterns
	int v=0;
	fore(i,0,sz(s)){
		char c=s[i];
		while(v && !to[v].count(c)) v=lnk[v];
		if(to[v].count(c)) v=to[v][c];
		for(int u=v;u;u=endlink[u]) for(int x: leaf[u]){
			ans[x].pb(i); //pushing the index of the main string where a pattern ends
		}  
	}
}
void doit(){
	string s;
	cin>>s; //main string.
	fore(i,0,n){
		cin>>a[i];
		add_str(a[i],i); //add target strings.
	}
	push_links();
	walk(s);
}