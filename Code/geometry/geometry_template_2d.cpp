struct Point {
	ld x, y;
	Point operator +(const Point& b) const { return Point{x+b.x, y+b.y};} 
	Point operator -(const Point& b) const { return Point{x-b.x, y-b.y}; } 
	ll operator *(const Point& b) const { return (ll) x * b.y - (ll) y * b.x; }
	Point operator *(const ld k)const{return Point{x*k,y*k};}
	bool operator <(const Point& b) const { return x == b.x ? y < b.y : x < b.x; }
	void operator +=(const Point& b) { x += b.x; y += b.y; }
	void operator -=(const Point &b) { x -= b.x; y -= b.y; }
	void operator *=(const int k) { x *= k; y *= k; }
	bool operator ==(const Point &b){
		if (b.x == (*this).x && b.y == (*this).y) return true;
		return false;
	}
	ld magnitude() const { return sqrt((x*x) + (y*y)); }
	ld dot (const Point &b){ return (x * b.x) + (y * b.y); }
	// If dot product > 0, angle between vectors is acute, = 0 vectors are perpendicular, and if < 0, angle is obtuse
	ld dist (const Point & b){return (*this - b).magnitude();} 
	ll cross(const Point& b, const Point& c) const {
		ll cruz = (b - *this) * (c - *this);
		if (cruz < 0) return -1; //cw (right)
		if (cruz > 0) return +1; //ccw (left)
		return 0; //Collinear.
	}
	ld rawCross(const Point &a, const Point &b) const { 
		return (a - *this) * (b - *this);
	}
	bool onSegment(Point p, Point r){ //point in a rectangular box
		if ((*this).x <= max(p.x, r.x) && (*this).x >= min(p.x, r.x) && (*this).y <= max(p.y, r.y) && (*this).y >= min(p.y, r.y)) return true;
		return false;
	}
	ld angleBetweenVectors(const Point &b){ //this: (b-a), Point b: (c-a).
		ld ang = acos((*this).dot(b)/((*this).magnitude() * b.magnitude()));
		ang = (ang * 180.0) / PI;
		return ang; //return angle in degrees.
	}
	int half() const { // for angular sorting, to know in which half is this
		if ((*this).y > 0) return 0;
		if ((*this).y < 0) return 1;
		return (*this).x >= 0 ? 0 : 1;
	}
};
struct LineToPoint{
	Point p1,p2;
	ld dist(Point refPoint){
		return abs((refPoint - p1) * (refPoint - p2)) / p1.dist(p2);
	}
};
ld degreesToRadians(ld degrees) { return degrees * PI / 180.0; }
ld radiansToDegrees(ld radians){ return radians * (180.0 / PI); }
Point rotate45(Point p){ // Rotates a point 45 degrees
	return {p.x + p.y, p.y - p.x};
}
Point undorotate45(Point p){ // Undo 45 degrees rotation of a point
	return {(p.x-p.y)/2, (p.y+p.x)/2};
}
bool angleCmp(const Point& a, const Point& b) { // for angular sorting
    int ha = a.half();
    int hb = b.half();
    if (ha != hb) return ha < hb;              // upper half first
    ll cr = a*b;
    if (cr != 0) return cr > 0;                // CCW order
    // Collinear: tie-break by distance from origin (shorter first, optional)
    return a.magnitude() < b.magnitude();
}
signed main(){}