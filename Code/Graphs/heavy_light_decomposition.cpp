//Tested with: https://cses.fi/problemset/task/2134/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
 
 
using namespace std;
 
const int maxn = 2e5+50;
const int neut = 0;
const int loga = 19;
int n,qrys,label_cont;
int up[maxn][loga],subt[maxn],dep[maxn],labe[maxn],arr[maxn],tp[maxn],revlabe[maxn],st[maxn*4],p[loga];
vector <int> adj[maxn];
 
void upd(int pos, int val, int node = 1, int ini = 1, int fin = n){
    if (ini == fin){
        st[node] = val;
        return;
    }
	int mid =(ini+fin)/2;
	if (pos <= mid) upd(pos,val,2*node,ini,mid);
    else upd(pos,val,2*node+1,mid+1,fin);
	st[node]=max(st[2*node],st[2*node+1]); // operation
}
int query(int l, int r, int node = 1, int ini = 1, int fin = n){
	if(fin < l || r < ini) return neut; // operation neutral
	if(l <= ini && fin <= r) return st[node];
	int mid =(ini+fin)/2;
	return max(query(l,r,2*node,ini,mid),query(l,r,2*node+1,mid+1,fin)); // operation
}
 
void init(){
    label_cont = 1;
    p[0] = 1;
    fore(i,1,loga) p[i] = (p[i-1] * 2LL);
}
 
int dfs_sz(int cur, int par) {
	subt[cur] = 1;
	for (int chi : adj[cur]) {
		if (chi == par) continue;
		dep[chi] = dep[cur] + 1;
		up[chi][0] = cur;
		subt[cur] += dfs_sz(chi, cur);
	}
	return subt[cur];
}
 
void dfs_hld(int cur, int par, int top) {
	labe[cur] = label_cont++;
	tp[cur] = top;
	upd(labe[cur], arr[cur]); //updating the STree using the labeling.
	int h_chi = -1, h_sz = -1;
	for (int chi : adj[cur]) {
		if (chi == par) continue;
		if (subt[chi] > h_sz) {
			h_sz = subt[chi];
			h_chi = chi;
		}
	}
	if (h_chi == -1) return;
	dfs_hld(h_chi, cur, top); //exploring the heavy edge first.
	for (int chi : adj[cur]) {
		if (chi == par || chi == h_chi) continue;
		dfs_hld(chi, cur, chi); //exploring the light edges.
	}
}
 
void binaryLift(){
    for (int i = 1; i<loga; i++){
        for (int j = 1; j<=n; j++) up[j][i] = up[up[j][i-1]][i-1];
    }
}
 
ll lca(ll x, ll y){
    if (x == y) return x;
    if (dep[x] > dep[y]) swap(x,y); //'y' is deeper.
    ll dif = dep[y] - dep[x];
    for (ll i = loga-1; i>=0; i--){
        ll pot = p[i];
        if (pot <= dif){
            dif -= pot;
            y = up[y][i];
        }
    }
    if (x == y) return x;
    for (ll i = loga-1; i>=0; i--){
        if (up[x][i] != up[y][i]){
            x = up[x][i];
            y = up[y][i];
        }
    }
    return up[x][0];
}
 
int pathQuery(int chi, int par) {
	int ret = 0;
	while (chi != par) {
		if (tp[chi] == chi) { //querying for the top of the chain, no STree needed.
			ret = max(ret, arr[chi]);
			chi = up[chi][0];
		} else if (dep[tp[chi]] > dep[par]) { //queyring for the whole chain.
			ret = max(ret, query(labe[tp[chi]], labe[chi]));
			chi = up[tp[chi]][0];
		} else { //querying for a part of the chain
			ret = max(ret, query(labe[par] + 1, labe[chi]));
			break;
		}
	}
	return ret;
}
 
int main(){
    fast;
    cin>>n>>qrys;
    init();
    fore(i,1,n+1) cin>>arr[i];
    fore(i,1,n){
        int x,y;
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs_sz(1,1);
    dfs_hld(1,1,1);
    binaryLift();
    while(qrys--){
        ll typ;
        cin>>typ;
        if (typ == 1){ //update a position with a new value
            ll node,val;
            cin>>node>>val;
            upd(labe[node],val);
            arr[node] = val;
        }
        else{ //query, path node - node2
            ll node,node2;
            cin>>node>>node2;
            ll lcan = lca(node,node2);
            ll q_ans = max({pathQuery(node,lcan),pathQuery(node2,lcan),arr[lcan]});
            cout<<q_ans<<" ";
        }   
    }
    cout<<nl;
    return 0;
}