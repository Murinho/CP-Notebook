struct Node{
	vi v;
	void order(){
		sort(ALL(v));
	}
	int get(int &val_l, int &val_r){ // cantidad de elementos [val_l, val_r]
        if (v.back() < val_l) return 0;
        
        int lwb = lower_bound(ALL(v), val_l) - v.begin();
        int upb = upper_bound(ALL(v), val_r) - v.begin();
        
        return upb-lwb;
    }
};

struct MSTree{
	vector <Node> st; int n;
	MSTree(int n): st(4*n + 5), n(n) {}
	void build(int node, int ini, int fin){ // mas rapido construir que hacer update valor por valor
		if (ini == fin){
			st[node].v.eb(a[ini]);
			return;
		}
		int mid = (ini+fin)/2;
		build(2*node,ini,mid);
		build(2*node + 1,mid+1,fin);
		
		merge(ALL(st[2*node].v),ALL(st[2*node + 1].v), back_inserter(st[node].v));
    }
	void upd(int node, int ini, int fin, int pos, int val){
		st[node].v.pb(val);
		if (ini == fin) return;
		int mid = (ini+fin)/2;
		if (pos <= mid) upd(2*node,ini,mid,pos,val);
		else upd(2*node + 1,mid+1,fin,pos,val);
	}
	int query(int node, int ini, int fin, int l, int r, int val_l, int val_r){
		if (fin < l || r < ini) return 0;
		if (l <= ini && fin <= r) return st[node].get(val_l,val_r);
		int mid = (ini+fin)/2;
		return (query(2*node,ini,mid,l,r,val_l,val_r)|query(2*node + 1,mid+1,fin,l,r,val_l,val_r));
	}
	void order(){ fore(i,1,4*n + 5) st[i].order();} // after all insertions, sort all nodes.
	void upd(int pos, int val){ upd(1,1,n,pos,val);}
	int query(int l, int r, int val_l, int val_r){ return query(1,1,n,l,r,val_l,val_r);}
	void build(){ build(1,1,n);}
};