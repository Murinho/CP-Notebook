// Tested with AC: https://codeforces.com/problemset/problem/87/E
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define rofe(i,a,b) for(ll i=a-1;i>=b;--i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define lsbpos(x) __builtin_ffs(x)
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second
#define eb emplace_back
#define ppb pop_back
#define i128 __int128_t
#define ull unsigned long long
 
using namespace std;

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
};

//////////////// POINT INSIDE POLYGON in O(NlogN)
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

//////////////// MINKOWSKI SUM
void reorder_polygon(vector<Point> & P){
    int pos = 0;
    for(int i = 1; i < sz(P); i++){ 
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<Point> minkowski(vector<Point> P, vector<Point> Q){
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.pb(P[0]);
    P.pb(P[1]);
    Q.pb(Q[0]);
    Q.pb(Q[1]);

    vector<Point> result;
    int i = 0, j = 0;
    while(i < sz(P) - 2 || j < sz(Q) - 2){
        result.pb(P[i] + Q[j]);
        ll cross = (P[i + 1] - P[i]) * (Q[j + 1] - Q[j]); // cross product
        if(cross >= 0 && i < sz(P) - 2) i++;
        if(cross <= 0 && j < sz(Q) - 2) j++;
    }
    return result;
}

vector <Point> pts[3];

int main(){
    fast;
    fore(i,0,3){
    		ll n;
    		cin >> n;
    		pts[i].resize(n);
    		fore(j,0,n){
    			ll x,y;
    			cin >> x >> y;
    			pts[i][j].x = x;
    			pts[i][j].y = y;
    		}
    }
    
    vector <Point> mk1 = minkowski(pts[0],pts[1]);
    vector <Point> mk2 = minkowski(pts[2],mk1);
    
    vector <Point> seq; //empty.
	Point translation;
	int k = sz(mk2);
	prepareConvexPolygon(k,mk2,seq,translation);
    
    int q;
    cin >> q;
    while(q--){
    		ll x,y;
    		cin >> x >> y;
    		Point qp;
    		qp.x = x*3;
    		qp.y = y*3;
    		if (pointInConvexPolygon(qp,k,seq,translation)) cout << "YES" << nl;
    		else cout << "NO" << nl;
    }
	return 0;
}