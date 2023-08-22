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