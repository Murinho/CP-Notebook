const ll maxn = 2e5+100;
ll a[maxn];

struct Node{
	ll max_sum,sumL,sumR,sum;
	Node operator+(Node b) {
		return {max(max(max_sum, b.max_sum), sumR + b.sumL),
					max(sumL, sum + b.sumL), max(b.sumR, sumR + b.sum),
					sum + b.sum};
	}
};

struct STree{
	vector <Node> st; int n;
	STree(int n): st(4*n + 5), n(n){}

	void build(int node, int ini, int fin){
		if (ini == fin){
			st[node] = {max(0ll, a[ini]), max(0ll, a[ini]), max(0ll, a[ini]), a[ini]};
			return;
		}
		int mid = (ini+fin)/2;
		build(2*node,ini,mid);
		build(2*node + 1,mid+1,fin);
		st[node] = st[2*node] + st[2*node + 1];
	}

	void update(int node, int ini, int fin, int pos, ll val){
		if (fin < pos || pos < ini) return;
		if (ini == fin && ini == pos){
			st[node] = {max(0ll, val), max(0ll, val), max(0ll, val), val};
			return;
		}
		ll mid = (ini+fin)/2;
		update(2*node,ini,mid,pos,val);
		update(2*node + 1,mid+1,fin,pos,val);
		st[node] = st[2*node] + st[2*node + 1];
	}

	void build(){ build(1,1,n);}
	void update(int pos, ll val){ update(1,1,n,pos,val);}
};

void doit(){
	// read values and build ST.
	// queries: st.st[1].max_sum
}