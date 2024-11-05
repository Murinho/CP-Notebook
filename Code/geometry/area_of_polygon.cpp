#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

struct Point{ ll x,y; };

Point operator +(const Point &A, const Point &B){
    return {A.x + B.x + A.y + B.y};
}
Point operator *(const Point &A, ll k){
    return {A.x * k, A.y * k};
}
Point operator -(const Point &A, const Point &B){
    return {A.x - B.x, A.y - B.y};
}
ll cross(const Point &A, const Point &B){
    return ((A.x*B.y) - (A.y*B.x));
}
ll turn(const Point &A, const Point &B, const Point &C){
    ll det = cross(B-A,C-A);
    return (det > 0 ? 1 : (det < 0 ? -1 : 0));
    //1: left.
    //-1: right.
    //0: in the line
}

bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;
  
    return false;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = turn(p1, q1, p2);
    int o2 = turn(p1, q1, q2);
    int o3 = turn(p2, q2, p1);
    int o4 = turn(p2, q2, q1);
  
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
  
    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
  
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
  
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
  
     // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
  
    return false; // Doesn't fall in any of the above cases
}

ll Area(vector <Point> poly){
    ll ans = 0;
    poly.push_back(poly.front());
    for (int i = 1; i<poly.size(); i++){
        ans += cross(poly[i-1],poly[i]);
    }
    return abs(ans);
}

vector <Point> p;
ll n,m;

void clean(){
    p.clear();
    p.resize(0);
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin>>n>>m;
    clean();
    for (int i = 0; i<n; i++){
        ll cx,cy;
        cin>>cx>>cy;
        p.pb({cx,cy});
    }
    cout<<Area(p)<<"\n";
    return 0;
}