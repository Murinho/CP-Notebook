//Code tested with: https://cses.fi/problemset/task/2195/
#include <bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define fast                                                                   \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0);

using namespace std;

const int maxN = 2e5+5;

struct Point {
    int x, y;
    void read(){ scanf("%d %d", &x, &y); }
    Point operator +(const Point& b) const { return Point{x+b.x, y+b.y}; }
    Point operator -(const Point& b) const { return Point{x-b.x, y-b.y}; }
    ll operator *(const Point& b) const { return (ll) x * b.y - (ll) y * b.x; }
    bool operator <(const Point& b) const { return x == b.x ? y < b.y : x < b.x; }
    void operator +=(const Point& b) { x += b.x; y += b.y; }
    void operator -=(const Point &b) { x -= b.x; y -= b.y; }
    void operator *=(const int k) { x *= k; y *= k; }

    ll cross(const Point& b, const Point& c) const {
        return (b - *this) * (c - *this);
    }
};

vector <Point> calculateHull(vector <Point> &P, int N){
    if (N <= 2) return P;
    vector<Point> hull;
    int S = 0;
    sort(P.begin(),P.end());
 
    for(int t = 0; t < 2; t++){
        for(int i = 0; i < N; i++){
            while((int) hull.size()-S >= 2){
                Point P1 = hull[hull.size()-2];
                Point P2 = hull[hull.size()-1];
                if(P1.cross(P2, P[i]) <= 0) break; //agregar <= si tambien se quieren incluir los colineales
                hull.pop_back();
            }
            hull.push_back(P[i]);
        }
        hull.pop_back();
        S = hull.size();
        reverse(P.begin(),P.end());
    }
 
    return hull;
}

 
int main(){
    int N, S;
    vector <Point> P;
    
    S = 0;
    cin>>N;
    P.resize(N);
    for(int i = 0; i < N; i++)
        P[i].read();
    
    vector <Point> hull = calculateHull(P,N);
    cout<<hull.size()<<nl;
    for (Point h : hull) cout<<h.x<<" "<<h.y<<nl;
    return 0;
}
