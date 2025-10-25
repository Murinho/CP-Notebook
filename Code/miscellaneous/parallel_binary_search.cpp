
bool changed=true;
while(changed){
	changed=false;
	// HERE CLEAR THE DATA STRUCTURE BEING USED!!
	fore(i,1,n+1){
		if (l[i] != r[i]) tocheck[(l[i] + r[i])/2].pb(i);
	}
	fore(i,1,q+1){
		apply(qs[i].l,qs[i].r); //Apply the i-th query on the DS.
		while(sz(tocheck[i])){
			changed=true;
			int id = tocheck[i].back();
			tocheck[i].pop_back();

			// Move l[id] and r[id] accordingly.
			if (check()) l[id] = i+1;
			else r[id]=i;
		}
	}
}