#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

using namespace std;

const ld INF = 1e4+100;
const ld eps = 1e-5;

struct Point {
    ld x, y; //cambiar tipo de dato de acuerdo al problema
    void read(){ cin>>x>>y; }
    Point operator +(const Point& b) const { return Point{x+b.x, y+b.y}; } //suma de puntos
    Point operator -(const Point& b) const { return Point{x-b.x, y-b.y}; } //resta de puntos
    ll operator *(const Point& b) const { return (ll) x * b.y - (ll) y * b.x; }
    bool operator <(const Point& b) const { return x == b.x ? y < b.y : x < b.x; }
    void operator +=(const Point& b) { x += b.x; y += b.y; }
    void operator -=(const Point &b) { x -= b.x; y -= b.y; }
    void operator *=(const int k) { x *= k; y *= k; }
    bool operator ==(const Point &b){
        if (b.x == (*this).x && b.y == (*this).y) return true;
        return false;
    }
    ld magnitude() const { return sqrt((x*x) + (y*y)); } //longitud hipotenusa
    ld dot (const Point &b){ return (x * b.x) + (y * b.y); } //producto punto. 
    // Si es el producto punto es positivo, el angulo entre los vectores es menor a º90 grados, igual a 0 los vectores son perpendiculares y si es negativo el angulo es obtuso.
    ld dist (const Point & b){ return (*this - b).magnitude(); } //distancia entre 2 puntos.
    ll cross(const Point& b, const Point& c) const { //Producto cruz
        ll cruz = (b - *this) * (c - *this);
        if (cruz < 0) return -1; //Clockwise (right)
        if (cruz > 0) return +1; //Counter-clockwise (left)
        return 0; //Collinear.
    }
    ll determinant(const Point &b){ return (((*this).x) * b.y) - ((*this).y * b.x); } //determinante 2x2
    bool onSegment(Point p, Point r){ //checa si un punto esta en el segmento entre dos puntos (delimitado como si fuera un rectangulo)
        if ((*this).x <= max(p.x, r.x) && (*this).x >= min(p.x, r.x) && (*this).y <= max(p.y, r.y) && (*this).y >= min(p.y, r.y)) return true;

        return false;
    }
    ld angleBetweenVectors(const Point &b){ //this: (b-a), Point b: (c-a).
        ld ang = acos((*this).dot(b)/((*this).magnitude() * b.magnitude()));
        ang = (ang * 180.0) / PI;
        return ang; //regresa el angulo en grados.
    }
};

ll n;
vector < pair <Point,ld> > v;

ld costf(Point p){
    ld res=0.0;
    fore(i,0,n){
        res = max(p.dist(v[i].fst) * v[i].snd,res);
    }
    return res;
}

ld get_y(ld x){
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

ld get_xy(){
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


int main(){ //do ternary search in 2D
    fast;
    cin>>n;
    fore(i,0,n){
        ld x,y,c;
        cin>>x>>y>>c;
        v.pb({{x,y},c});
    }
    cout<<fixed<<setprecision(10)<<get_xy()<<nl;
    return 0;
}