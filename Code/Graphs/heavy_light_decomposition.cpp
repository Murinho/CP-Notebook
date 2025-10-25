const int maxn = 2e5+50;
const int neut = 0;
const int loga = 19;
int n,qrys,label_cont;
int up[maxn][loga],subt[maxn],dep[maxn],labe[maxn],arr[maxn],tp[maxn],revlabe[maxn],st[maxn*4],p[loga];
vi adj[maxn];
 
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
	// if assigning value here do: arr[labe[cur]] = val
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
	fore(i,1,loga){
		fore(j,1,n+1) up[j][i] = up[up[j][i-1]][i-1];
	}
}
 
ll lca(ll x, ll y){
	if (x == y) return x;
	if (dep[x] > dep[y]) swap(x,y); //'y' is deeper.
	ll dif = dep[y] - dep[x];
	rofe(i,loga,0){
		if (p[i] <= dif){
			dif -= p[i];
			y = up[y][i];
		}
	}
	if (x == y) return x;
	rofe(i,loga,0){
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
			ret = max(ret, query(labe[chi], labe[chi])); // or do max(ret, arr[chi]) if arr[chi] is kept updated.
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

void doit(){ //Example querying and updating for maximum value.
	init();
	// 1. Read initial values for each node.
	// 2. Read and create adjacency list.
	dfs_sz(1,1);
	dfs_hld(1,1,1);
	binaryLift();
	// for updates:
	upd(labe[node],val);
	arr[node] = val;
	// or do the same as pathQuery but updating.

	// for queries:
	ll lcan = lca(node,node2); 
	ll q_ans = max({pathQuery(node,lcan),pathQuery(node2,lcan),arr[lcan]});
}