#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double

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

struct P{
    ld x,y;
    void read(){ cin>>x>>y; }
    P operator + (P b){ return P{x + b.x, y + b.y}; } //suma de puntos
    P operator - (P b){ return P{x - b.x, y - b.y}; } //resta de puntos
    P operator * (ld mul){ return P{x * mul, y * mul}; }
    ld operator * (P b){ return (x*b.y) - (y*b.x); }
    ld dot (P b){ return (x * b.x) + (y * b.y); } //producto punto
    ld len(){ return sqrt((x*x) + (y*y)); } //longitud hipotenusa
    P lenTo(ld to){ return *this * (to/len()); }
    ld dist (P & b){ return (*this - b).len(); } //distancia entre 2 puntos.
};

struct Line2Point{
    P one,two;
    ld dist(P refPoint){
        return abs((refPoint - one) * (refPoint - two)) / one.dist(two);
    }
};


int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    ll tc;
    cin>>tc;
    while(tc--){
        ll ax,ay,bx,by,cx,cy;
        cin>>ax>>ay>>bx>>by>>cx>>cy;
        Point a = {ax,ay};
        Point b = {bx,by};
        Point c = {cx,cy};
        ll ans = turn(a,b,c);
        if (ans == 1) cout<<"LEFT\n";
        else if (ans == -1) cout<<"RIGHT\n";
        else cout<<"TOUCH\n";
    }
    return 0;
}