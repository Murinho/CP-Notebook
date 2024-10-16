#include <bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define ld long double
#define fast                                                                   \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define PI acos(-1.0)
#define ALL(u) u.begin(),u.end()

using namespace std;

const ld EPS = 1e-6;
const ld pi = 3.1415926535;
const ll INF = 1e18;

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
    ld rawCross(const Point &a, const Point &b) const { 
		return (a - *this) * (b - *this);
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

struct LineToPoint{ //calcula la distancia entre un punto y una recta.
    Point p1,p2;
    ld dist(Point refPoint){
        return abs((refPoint - p1) * (refPoint - p2)) / p1.dist(p2);
    }
};

int sgn(ll val) { return val > 0 ? 1 : (val == 0 ? 0 : -1); }

bool pointInTriangle(Point a, Point b, Point c, Point point){
    ll s1 = abs(a.rawCross(b, c));
    ll s2 = abs(point.rawCross(a, b)) + abs(point.rawCross(b, c)) + abs(point.rawCross(c, a));
    return s1 == s2;
}

//Precalculation for queries to know if a point lies inside of a convex polygon.
void prepareConvexPolygon(int &n, vector<Point> &points, vector<Point> &seq, Point &translation){ //seq and translation are empty here.
    n = points.size();
    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (points[i] < points[pos])
            pos = i;
    }
    rotate(points.begin(), points.begin() + pos, points.end());

    n--;
    seq.resize(n);
    for (int i = 0; i < n; i++)
        seq[i] = points[i + 1] - points[0];
    translation = points[0];
}

//Know if a point lies inside of a convex polygon in O(logN)
bool pointInConvexPolygon(Point point, int &n, vector<Point> &seq, Point &translation) {
    point = point - translation;
    if (seq[0]*point != 0 && sgn(seq[0]*point) != sgn(seq[0]*seq[n-1])) return false;
    if (seq[n - 1]*point != 0 && sgn(seq[n - 1]*point) != sgn(seq[n - 1]*seq[0])) return false;
	if (seq[0]*point == 0) return seq[0].dot(seq[0]) >= point.dot(point);
	int l = 0, r = n - 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        int pos = mid;
        if (seq[pos]*point >= 0) l = mid;
		else r = mid;
    }
    int pos = l;
    return pointInTriangle(seq[pos], seq[pos + 1], Point{0,0}, point);
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2){ //Checa si 2 lineas se intersectan o no.
    // Find the four orientations needed for general and
    // special cases
    int o1 = p1.cross(q1, p2);
    int o2 = p1.cross(q1, q2);
    int o3 = p2.cross(q2, p1);
    int o4 = p2.cross(q2, q1);
  
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
  
    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && p2.onSegment(p1, q1)) return true;
  
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && q2.onSegment(p1, q1)) return true;
  
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && p1.onSegment(p2, q2)) return true;
  
     // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && q1.onSegment(p2, q2)) return true;
  
    return false; // Doesn't fall in any of the above cases
}

vector <Point> calculateHull(vector <Point> &P, int N){ //Calculo del Convex Hull
    if (N <= 2) return P;
    vector<Point> hull;
    int S = 0;
    sort(P.begin(),P.end());
 
    for(int t = 0; t < 2; t++){
        for(int i = 0; i < N; i++){
            while((int) hull.size()-S >= 2){
                Point P1 = hull[hull.size()-2];
                Point P2 = hull[hull.size()-1];
                //Producto cruz: P1 ---> P2 ---> P3 
                if(P1.cross(P2, P[i]) <= 0) break; //agregar (<=) si tambien se quieren incluir los puntos colineales, sino solo (<)
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

ll Area(vector <Point> poly){ //Calculo de area de poligono
    ll ans = 0;
    poly.push_back(poly.front());
    for (int i = 1; i<poly.size(); i++){
        ans += poly[i-1].determinant(poly[i]);
    }
    return abs(ans);
}


vector <Point> circleLineIntersection(double a, double b, double c, double r){ 
//Dados los coeficientes de la ecuacion de la recta y el radio del circulo con centro en el origen
    vector <Point> pts;
    double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)+EPS){
        //puts ("no points");
    }
    else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
        //puts ("1 point");
        //cout << x0 << ' ' << y0 << '\n';
        pts.pb({x0,y0});
    }
    else {
        double d = r*r - c*c/(a*a+b*b);
        double mult = sqrt (d / (a*a+b*b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        //puts ("2 points");
        pts.pb({ax,ay});
        pts.pb({bx,by});
    }
    return pts;
}

vector <double> ecuacionDeRecta(Point p1, Point p2){ //dados 2 puntos de una recta, devuelve los coeficientes de Ax + By + C = 0
    double a = p1.y-p2.y;
    double b = p2.x-p1.x;
    double c = -(a*p1.x) - (b*p1.y);
    return {a,b,c};
}

string checkPointInsidePolygon(vector <Point> P, Point point, int n){ //checa si un punto dado esta DENTRO, FUERA o en FRONTERA con un poligono
    P[0] = point;
    ll count = 0;
    if (n < 3) return "OUTSIDE";
    for (int i = 1; i<=n; i++){
        int j = (i == n ? 1 : i+1);
        if(P[i].x <= P[0].x && P[0].x < P[j].x && P[0].cross(P[i], P[j]) < 0)       count++;
        else if(P[j].x <= P[0].x && P[0].x < P[i].x && P[0].cross(P[j], P[i]) < 0)  count++;
        
        if ((min(P[i].x,P[j].x) <= point.x && point.x <= max(P[i].x,P[j].x)) && (min(P[i].y,P[j].y) <= point.y && point.y <= max(P[i].y,P[j].y)) && point.cross(P[i],P[j]) == 0){
            return "BOUNDARY";
        }
    }
    if (count%2 == 1) return "INSIDE";
    return "OUTSIDE";
}

bool checkParallelism(Point p1, Point p2, Point p3, Point p4){ //(p1 -- p2) es una linea (p3 -- p4) es la otra linea.
    double v1x = p2.x - p1.x;
    double v1y = p2.y - p1.y;
    double v2x = p4.x - p3.x;
    double v2y = p4.y - p3.y;
    double crossProd = (v1x*v2y) - (v1y*v2x);
    return abs(crossProd) < EPS; //son paralelas si su producto cruz = 0.
}

bool checkPerpendicular(Point p1, Point p2, Point p3, Point p4){ //(p1 -- p2) es una linea (p3 -- p4) es la otra linea.
    double v1x = p2.x - p1.x;
    double v1y = p2.y - p1.y;
    double v2x = p4.x - p3.x;
    double v2y = p4.y - p3.y;
    double dotProduct = v1x * v2x + v1y * v2y;
    return abs(dotProduct) < EPS;
}

double volumeSphere(double rad){ 
    return (4.0/3.0)*pi*rad*rad*rad;
}
 
double volumeCap(double h, double rad){ //parte de una esfera.
    return pi*h*h*(rad-(h/3.0));
}

ld angleBetweenPoints(Point A, Point B, Point C) { //Angulo formado por los vectores AB, AC.
    Point AB = {B.x - A.x, B.y - A.y};
    Point AC = {C.x - A.x, C.y - A.y};

    ld dot = AB.dot(AC);

    ld mag_AB = AB.magnitude();
    ld mag_AC = AC.magnitude();

    ld angle_rad = acos(dot / (mag_AB * mag_AC));
    ld angle_deg = angle_rad * 180.0 / pi;
    
    return angle_deg;
}

ld degreesToRadians(ld degrees) {
    return degrees * pi / 180.0;
}

ll closestPair(vector <pair<ll,ll> > pts){ //Calcula el par de puntos en 2D mas cercanos entre si, retorna su distancia euclidiana.
	int n = pts.size();
    sort(ALL(pts));
    set<pair<ll,ll>> s;

	ll ans = INF;
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        ll d = ceil(sqrt(ans));
        while (pts[i].first - pts[pos].first >= d) {
            s.erase({pts[pos].second, pts[pos].first});
            pos++;
        }

        auto it1 = s.lower_bound({pts[i].second - d, pts[i].first});
        auto it2 = s.upper_bound({pts[i].second + d, pts[i].first});
        
        for (auto it = it1; it != it2; it++) {
            ll dx = pts[i].first - it->second;
            ll dy = pts[i].second - it->first;
			if (ans > 1LL * dx * dx + 1LL * dy * dy){
				ans = 1LL * dx * dx + 1LL * dy * dy;
			} 
        } 
        s.insert({pts[i].second, pts[i].first}); 
    }
	return ans;
}

signed main() {
    fast;
}