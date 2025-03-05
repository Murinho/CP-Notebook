int fn,sn;
vector <bool> used;
vector <int> mt;
vvi g;

bool kuhn(int v){
	if (used[v]) return false;
	used[v]=true;
	for(int to : g[v]){ //simple adjacency list.
		if (mt[to] == -1 || kuhn(mt[to])){
			mt[to]=v;
			return true;
		}
	}
	return false;
}

ll do_kuhn(){  //Complexity: O(n*m)
	mt.assign(sn,-1); //sn is the size of the second (right) part size of the graph.
	ll mm = 0;
	fore(v,0,fn){ //fn is the size of the first(left) part size of the graph.
		used.assign(fn,false);
		if(kuhn(v)) mm++;
	}
	
	/* mt[i] this is the number of the vertex of the first part connected by an edge 
	with the vertex i of the second part (or -1, if no matching edge comes out of it). */
	
	fore(i,0,sn){
		if (mt[i] != -1) cout<<"Connection: "<<mt[i] + 1<<" (left part) -- > "<<i + 1<<" (right part)"<<nl;	
	}
	return mm; //maximum matching.
}