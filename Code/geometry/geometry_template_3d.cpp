struct point3{
	ld x,y,z;
	void read(){
		cin>>x>>y>>z;
	} 
	point3(): x(0), y(0), z(0) {}
	point3(ld x, ld y, ld z): x(x), y(y), z(z) {}
	point3 operator - (const point3 &b) const { return point3(x - b.x, y - b.y, z - b.z);}
	bool operator == (const point3 &b) const {return x == b.x && y == b.y && z == b.z;}
	ld dot(const point3 &b) const { return x*b.x + y*b.y + z*b.z;}
	point3 cross(const point3 &b) const { return {(y*b.z) - (z*b.y), (z*b.x) - (x*b.z), (x*b.y) - (y*b.x)};}
};

struct plane{
	point3 n; ld d;
	plane(): n(0,0,0), d(0) {}
	plane(point3 n, ld d): n(n), d(d) {}
	plane(point3 p1, point3 p2, point3 p3): plane((p2-p1).cross(p3-p1), p1.dot((p2-p1).cross(p3-p1))) {} // Initialize by giving 3 points in the plane.
	ld side(const point3 &p) const { return ((*this).n).dot(p) - (*this).d;}
    /*
    If side(p) > 0: The point p is on the positive side of the plane (in the direction of the normal).
    If side(p) < 0: The point p is on the negative side of the plane.
    If side(p) == 0: The point p lies on the plane.
    */
};