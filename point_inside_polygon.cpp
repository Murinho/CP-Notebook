#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define nl '\n'
#define ll long long
#define fast                                                                   \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define X real()
#define Y imag()
#define pb push_back
#define ld long double
 
ll n,m;

struct Point {
    ld x,y;
    void read(){ cin>>x>>y; }
    Point operator +(const Point& b) const { return Point{x+b.x, y+b.y}; } //suma de puntos
    Point operator -(const Point& b) const { return Point{x-b.x, y-b.y}; } //resta de puntos
    ld operator *(const Point& b) const { return (ll) x * b.y - (ll) y * b.x; }
    Point operator * (ld mul){ return Point{x * mul, y * mul}; } //relocate point proportionally
    void operator +=(const Point& b) { x += b.x; y += b.y; } 
    void operator -=(const Point& b) { x -= b.x; y -= b.y; }
    void operator *=(const int k) { x *= k; y *= k; }
    ld len(){ return sqrt((x*x) + (y*y)); } //longitud hipotenusa
    Point lenTo(ld to){ return (*this)*(to/len()); } 
    ld dist (Point & b){ return (*this - b).len(); } //distancia entre 2 puntos.

    ld cross(const Point& b, const Point& c) const {
        return (b - *this) * (c - *this);
    }
};

vector <Point> P;
 
string checkInside(Point point){
    P[0] = point;
    ll count = 0;
    if (n < 3) return "OUTSIDE";
    for (int i = 1; i<=n; i++){
        int j = (i == n ? 1 : i+1);
        if(P[i].x <= P[0].x && P[0].x < P[j].x && P[0].cross(P[i], P[j]) < 0)       count++;
        else if(P[j].x <= P[0].x && P[0].x < P[i].x && P[0].cross(P[j], P[i]) < 0)  count++;
        //check if point lies on the edge
        if ((std::min(P[i].x,P[j].x) <= point.x && point.x <= std::max(P[i].x,P[j].x)) && (std::min(P[i].y,P[j].y) <= point.y && point.y <= std::max(P[i].y,P[j].y)) && point.cross(P[i],P[j]) == 0){
            return "BOUNDARY";
        }
    }
    if (count%2 == 1) return "INSIDE";
    return "OUTSIDE";
}
 
 
signed main() {
    fast;
    cin >> n >> m;
    P.resize(n+1);
    for (int i = 1; i <=n; i++) {
        ld x, y;
        cin >> x >> y;
        P[i] = {x, y};
    }
    //How to tell if a point is inside a polygon or not given the polygon.
    for (int i = 1; i<=m; i++){
        ld x,y;
        Point punto;
        cin>>x>>y;
        punto = {x,y};
        cout<<checkInside(punto)<<nl;
    }
    return 0;
}