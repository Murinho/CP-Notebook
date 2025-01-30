struct UnionFind{
    int ran,pad,tam;
};
UnionFind uf[maxn];

int bus(int u){
	if (uf[u].pad!=u) uf[u].pad=bus(uf[u].pad);
	return uf[u].pad;
}

void unir(int u ,int v){
	u=bus(u); v=bus(v);
	if (u==v) return; 
	if (uf[u].ran>uf[v].ran){
        uf[v].pad=u;
        uf[u].tam+=uf[v].tam;
    }
	else if (uf[u].ran<uf[v].ran) {
        uf[u].pad=v;
        uf[v].tam+=uf[u].tam;
    }
	else {
        uf[u].pad=v;
        uf[v].ran++;
        uf[v].tam+=uf[u].tam;
    }
	return;
}

void init(){
    fore(i,0,n){
        uf[i].pad = i;
        uf[i].ran = 0;
        uf[i].tam = 1;
    }
}
