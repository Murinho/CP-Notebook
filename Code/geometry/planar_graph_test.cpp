// Tested with: https://codeforces.com/gym/105431/problem/F
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a; i<b; i++)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector <vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second
#define RB(x) (x<n?r[x]:0)

using namespace std;

struct Point {
    ll x, y; //cambiar tipo de dato de acuerdo al problema
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
    ll cross(const Point& b, const Point& c) const { //Producto cruz
        ll cruz = (b - *this) * (c - *this);
        if (cruz < 0) return -1; //Clockwise (right)
        if (cruz > 0) return +1; //Counter-clockwise (left)
        return 0; //Collinear.
    }
};

ld shoelace(vector <Point> poly){ //Calculo de area de poligono
    ld ans = 0;
    poly.push_back(poly.front());
    for (int i = 1; i<poly.size(); i++){
        ans += (poly[i-1]*poly[i]);
    }
    return abs(ans)/2.0;
}

// Sort the points counterclockwise around a reference point
bool sort_ccw(const Point& p, const Point& a, const Point& b) {
    return atan2(a.y - p.y, a.x - p.x) < atan2(b.y - p.y, b.x - p.x);
}

// Find a face of the graph
vector<Point> find_face(map<Point, vector<Point>>& neighbors, const Point& u, const Point& v) {
    vector<Point> face;
    Point current = v, previous = u;

    face.pb(previous);
    while (true) {
        face.pb(current);
        vector<Point>& current_neighbors = neighbors[current];
        auto index = find(ALL(current_neighbors), previous) - current_neighbors.begin();
        int next_index = (index + 1) % sz(current_neighbors);
        Point next_vertex = current_neighbors[next_index];
        if (next_vertex.x == u.x && next_vertex.y == u.y) break;
        previous = current;
        current = next_vertex;
    }
    face.pb(u);
    return face;
}

// Find the outer edge of the graph
pair<Point, Point> find_outer_edge(map<Point, vector<Point>>& mp) {
    auto leftmost = min_element(ALL(mp), [](const pair<Point, vector<Point>>& a, const pair<Point, vector<Point>>& b) {
        return tie(a.first.x, a.first.y) < tie(b.first.x, b.first.y);
    })->first;

    vector<Point>& N_leftmost = mp[leftmost];
    sort(ALL(N_leftmost), [&leftmost](const Point& a, const Point& b) {
        return sort_ccw(leftmost, a, b);
    });

    Point u = N_leftmost[0];
    return {leftmost, u};
}

int main(){ //Computes the faces of the planar graph and then calculates its area.
    fast;
    int n;
    cin>>n;

    map<Point, vector<Point>> mp; //adjacency list.
    set<pair<Point, Point>> seen; //seen edges.

    for (int i = 0; i < n; ++i) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Point p1 = {x1,y1}, p2 = {x2,y2};
        mp[p1].pb(p2);
        mp[p2].pb(p1);
    }

    for (auto& p : mp) {
        //Sort each adjacency list in counter-clockwise order.
        sort(ALL(p.second), [&p](const Point& a, const Point& b) {
            return sort_ccw(p.first, a, b);
        });
    }

    auto [p, q] = find_outer_edge(mp);
    vector<Point> outer = find_face(mp, p, q);

    fore(i,0,sz(outer)-1) seen.insert({outer[i], outer[(i+1)%sz(outer)]});

    ld total_area = 0.0;
    for (const auto& p : mp) {
        for (const auto& q : p.second) {
            if (seen.count({p.first, q})) continue;
            seen.insert({p.first, q});
            vector<Point> face = find_face(mp, p.first, q);
            ld face_area = shoelace(face);
            total_area += (face_area*face_area);
            fore(i,0,sz(face)-1) seen.insert({face[i], face[(i+1)%sz(face)]});
        }
    }
    cout<<fixed<<setprecision(18)<<total_area<<nl;
    return 0;
}
