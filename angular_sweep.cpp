//Tested with: https://www.spoj.com/problems/ADAPICK/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((int)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
 
using namespace std;

struct Point{
    ll x,y,nume,denom,idx,typ,quad;
};

ll quadrantLocation(Point p){ //4 quadrants in 2D space.
    if (p.x == 0 || p.y == 0){
        if (p.x == 0 && p.y == 0) return 0; //origin.
        else if (p.y == 0){
            if (p.x > 0) return 1;
            else return 3;
        }
        else{
            if (p.y > 0) return 2;
            else return 4;
        }
    }
    else{
        if (p.x > 0 && p.y > 0) return 1;
        else if (p.x < 0 && p.y > 0) return 2;
        else if (p.x < 0 && p.y < 0) return 3;
        else return 4;
    }
}

ll tc,n;
vector <Point> a,q1,q2,q3,q4;
vector <ll> active;

void init(){
    a.clear(), a.resize(0);
    q1.clear(), q1.resize(0);
    q2.clear(), q2.resize(0);
    q3.clear(), q3.resize(0);
    q4.clear(), q4.resize(0);
    active.clear(), active.resize(n+1);
}

bool cmp(Point p1, Point p2){
    ll f1 = p1.nume*p2.denom;
    ll f2 = p1.denom*p2.nume;
    if (f1 == f2){
        return p1.typ < p2.typ;
    }
    return f1 < f2;
}

void toqVector(Point &p){
    if (p.quad == 1) q1.pb(p);
    else if (p.quad == 2) q2.pb(p);
    else if (p.quad == 3) q3.pb(p);
    else q4.pb(p);
}

ld findXIntercept(Point p1, Point p2) {
    // Calculate the slope
    ld m = (ld)(p2.y - p1.y) / (ld)(p2.x - p1.x);

    // Calculate the y-intercept (b) using one of the points
    ld b = p1.y - m * p1.x;

    // Calculate the x-coordinate where y = 0
    ld xIntercept = -b / m;

    return xIntercept;
}

void angularSort(){
    sort(ALL(q1),cmp);
    sort(ALL(q2),cmp);
    sort(ALL(q3),cmp);
    sort(ALL(q4),cmp);
    for(auto elm : q1) a.pb(elm);
    for(auto elm : q2) a.pb(elm);
    for(auto elm : q3) a.pb(elm);
    for(auto elm : q4) a.pb(elm);
}

void angularSweep(){
    ll pos = 0;
    ll cnt = 0;
    ll cur = 0;
    ll ans = 0;
    while(cnt < 2*n){ //pass through all points twice.
        if (a[pos].typ == 1){ //activate
            cur++;
            active[a[pos].idx] = 1;
            ans = max(ans,cur);
        }
        else{ //deactivate
            if (active[a[pos].idx] == 1){
                cur--;
                active[a[pos].idx] = 0;
                cnt++;
            }
        }
        pos = (pos+1)%(2*n);
    }
    cout<<ans<<nl;
}

void lineSettings(){
    fore(i,0,n){
        Point p1,p2;
        cin>>p1.x>>p1.y>>p2.x>>p2.y;
        p1.idx = p2.idx = i;
        ll g1 = __gcd(abs(p1.x),abs(p1.y));
        ll g2 = __gcd(abs(p2.x),abs(p2.y));
        p1.nume = p1.y/g1;
        p1.denom = p1.x/g1;
        p2.nume = p2.y/g2;
        p2.denom = p2.x/g2;
        p1.quad = quadrantLocation(p1);
        p2.quad = quadrantLocation(p2);
        if (p1.quad > p2.quad) swap(p1,p2); //p1 estara en un cuadrante mas chico siempre.

        if (p1.quad == 1 && p2.quad == 3){
            ld xInt = findXIntercept(p1,p2);
            if (xInt > 0.0){
                p2.typ = 1;
                p1.typ = 2;
            }
            else{
                p1.typ = 1;
                p2.typ = 2;
            }
        }
        else if (p1.quad == 1 && p2.quad == 4){
            p1.typ = 2;
            p2.typ = 1;
        }
        else if (p1.quad == 2 && p2.quad == 4){
            ld xInt = findXIntercept(p1,p2);
            if (xInt > 0.0){
                p2.typ = 1;
                p1.typ = 2;
            }
            else{
                p1.typ = 1;
                p2.typ = 2;
            }
        }
        else{
            if (p1.quad == p2.quad){
                vector <Point> aux;
                aux.pb(p1);
                aux.pb(p2);
                sort(ALL(aux),cmp);
                p1 = aux[0];
                p2 = aux[1];
                p1.typ = 1;
                p2.typ = 2;
            }
            else if (p1.quad < p2.quad){
                p1.typ = 1;
                p2.typ = 2;
            }
        }
        toqVector(p1);
        toqVector(p2);
    }
}

int main(){
    fast;	
    ll tc;
    cin>>tc;
    while(tc--){
        cin>>n;
        init();
        lineSettings();
        angularSort();
        angularSweep();
    }
    return 0;
}