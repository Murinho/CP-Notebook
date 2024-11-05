#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double

using namespace std;

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

ll cross(const P &A, const P &B){
    return ((A.x*B.y) - (A.y*B.x));
}
ll turn(P &A, P &B, P &C){
    ll det = cross(B+A,C+A);
    return (det > 0 ? 1 : (det < 0 ? -1 : 0));
    //1: left.
    //-1: right.
    //0: in the line
}




int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    ll tc;
    cin>>tc;
    while(tc--){
        ll ax,ay,bx,by,cx,cy;
        cin>>ax>>ay>>bx>>by>>cx>>cy;
        P a = {ax,ay};
        P b = {bx,by};
        P c = {cx,cy};
        ll ans = turn(a,b,c);
        if (ans == 1) cout<<"LEFT\n";
        else if (ans == -1) cout<<"RIGHT\n";
        else cout<<"TOUCH\n";
    }
    return 0;
}