const ld INF = 1e4+100, eps = 1e-5;
struct Point{ld x,y;};
ld costf(Point p){return 0;}
ld get_y(ld x){ // looking for minimums.
	ld l = -INF;
	ld r = INF;
	while(r - l > eps){
		ld m1 = l + (r - l) / 3;
		ld m2 = r - (r - l) / 3;
		Point p1,p2;
		p1 = {x,m1}, p2 = {x,m2};
		ld f1 = costf(p1)*(-1);
		ld f2 = costf(p2)*(-1);
		if (f1 < f2) l = m1;
		else r = m2;
	}
	return costf({x,{(l+r)/2}});
}
ld get_xy(){ // looking for minimums.
	ld l = -INF;
	ld r = INF;
	while(r - l > eps){
		ld m1 = l + (r - l) / 3;
		ld m2 = r - (r - l) / 3;
		ld f1= get_y(m1)*(-1);
		ld f2 = get_y(m2)*(-1);
		if (f1 < f2) l = m1;
		else r = m2;
	}
	return get_y((l+r)/2);
}
void doit(){ 
	cout<<fixed<<setprecision(10)<<get_xy()<<nl;
}