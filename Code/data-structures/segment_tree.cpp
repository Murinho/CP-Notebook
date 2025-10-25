const ll maxn = 2e5+10;
ll a[maxn];

struct STree{
	vi st; int n;
	STree(int n): st(4*n + 5),n(n){}

	void build(int node,int ini,int fin){
		if (ini == fin) { 
			st[node] = a[ini];
			return;
		}
		int mid = (ini+fin)/2;
		build(2*node,ini,mid); //Left sohn
		build(2*node + 1,mid+1,fin); //Right sohn
		st[node] = (st[2*node] + st[2*node + 1]); //desired operation
		return;
	}
	ll query(int node,int ini,int fin,int l,int r){
		if (l <= ini && fin <= r) return st[node]; //Fully in
		if (ini > r || fin < l) return 0; //Fully out
		int mid = (ini+fin)/2;
		return (query(2*node,ini,mid,l,r) + query(2*node + 1,mid+1,fin,l,r)); 
	}
	void upd(int node,int ini,int fin,int pos, ll val){
		if (fin < pos || pos < ini) return; //Fully out
		if (ini == fin && ini == pos) { 
			st[node] = val;
			return;
		}
		int mid = (ini+fin)/2;
		upd(2*node,ini,mid,pos,val);  
		upd(2*node + 1,mid+1,fin,pos,val); 
		st[node] = (st[2*node] + st[2*node + 1]);
		return;
	}
	void build(){ build(1,1,n);}
	void upd(int pos, ll val){ upd(1,1,n,pos,val);}
	ll query(int l, int r){ return query(1,1,n,l,r);}
};