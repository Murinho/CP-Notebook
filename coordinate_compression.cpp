//Coordinate compression:

#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define nl '\n'
#define lsb(x) ((x)&(-x))
 
using namespace std;

struct Query{
	char c;
	int l,r;
};

int n,qrs,ans;
vector <int> st;
unordered_map <int,int> mp;
const int maxn = 2e5+5;
const int mxfen = 6e5+15;
Query q[maxn];
int a[maxn],fen[mxfen];

void add(int pos, int val){
	while(pos <= mxfen-5){
		fen[pos] += val;
		pos += lsb(pos);
	}
}

int get(int pos){
	ll freq = 0;
	while(pos > 0){
		freq += fen[pos];
		pos -= lsb(pos);
	}
	return freq;
}

 
int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	int pos = 1;
	cin>>n>>qrs;
	for (int i = 1; i<=n; i++){
		cin>>a[i];
		st.pb(a[i]);
	}

	for (int i = 1; i<=qrs; i++){
		Query aux;
		cin>>aux.c>>aux.l>>aux.r;
		if (aux.c == '?') st.pb(aux.l);
		st.pb(aux.r);
		q[i] = aux;
	}
	sort(st.begin(),st.end());
	st.erase(unique(st.begin(),st.end()),st.end());
	for (auto au : st){
		mp[au] = pos;
		pos++;
	}
	for (int i = 1; i<=n; i++){
		add(mp[a[i]],1);
	}
	//cout<<"Now process queries: "<<nl;
	for (int i = 1; i<=qrs; i++){
		if (q[i].c == '!'){ //change salary
			int k = q[i].l;
			add(mp[a[k]],-1);
			a[k] = q[i].r;
			add(mp[a[k]],1);
		}
		else{ //get query
			int r = mp[q[i].r];
			int l = mp[q[i].l];
			ans = get(r);
			if (l > 1) ans -= get(l-1);
			cout<<ans<<nl;
		}
	}
	return 0;
}