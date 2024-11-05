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
 
ll n,m;

struct Point {
    int x, y;
    Point operator +(const Point& b) const { return Point{x+b.x, y+b.y}; }
    Point operator -(const Point& b) const { return Point{x-b.x, y-b.y}; }
    ll operator *(const Point& b) const { return (ll) x * b.y - (ll) y * b.x; }
    void operator +=(const Point& b) { x += b.x; y += b.y; }
    void operator -=(const Point& b) { x -= b.x; y -= b.y; }
    void operator *=(const int k) { x *= k; y *= k; }

    ll cross(const Point& b, const Point& c) const {
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
        int x, y;
        cin >> x >> y;
        P[i] = {x, y};
    }
    //How to tell if a point is inside a polygon or not given the polygon.
    for (int i = 1; i<=m; i++){
        ll x,y;
        Point punto;
        cin>>x>>y;
        punto = {x,y};
        cout<<checkInside(punto)<<nl;
    }
    return 0;
}