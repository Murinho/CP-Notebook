int sgn(ll val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }

bool pointInTriangle(Point a, Point b, Point c, Point point){
	ll s1 = abs(a.rawCross(b, c));
	ll s2 = abs(point.rawCross(a, b)) + abs(point.rawCross(b, c)) + abs(point.rawCross(c, a));
	return s1 == s2;
}

//Precalculation for queries to know if a point lies inside of a convex polygon.
void prepareConvexPolygon(int &n, vector<Point> &points, vector<Point> &seq, Point &translation){ //seq and translation are empty here.
	n = points.size();
	int pos = 0;
	for (int i = 1; i < n; i++) {
		if (points[i] < points[pos])
			pos = i;
	}
	rotate(points.begin(), points.begin() + pos, points.end());

	n--;
	seq.resize(n);
	for (int i = 0; i < n; i++)
		seq[i] = points[i + 1] - points[0];
	translation = points[0];
}

//Know if a point lies inside of a convex polygon in O(logN)
bool pointInConvexPolygon(Point point, int &n, vector<Point> &seq, Point &translation) {
	point = point - translation;
	if (seq[0]*point != 0 && sgn(seq[0]*point) != sgn(seq[0]*seq[n-1])) return false;
	if (seq[n - 1]*point != 0 && sgn(seq[n - 1]*point) != sgn(seq[n - 1]*seq[0])) return false;
	if (seq[0]*point == 0) return seq[0].dot(seq[0]) >= point.dot(point);
	int l = 0, r = n - 1;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		int pos = mid;
		if (seq[pos]*point >= 0) l = mid;
		else r = mid;
	}
	int pos = l;
	return pointInTriangle(seq[pos], seq[pos + 1], Point{0,0}, point);
}

void doit(){
	int n;
	vector <Point> poly; //with input.
	vector <Point> seq; //empty.
	Point translation;
	prepareConvexPolygon(n,poly,seq,translation);
	// then call pointInConvexPolygon() for queries.
}