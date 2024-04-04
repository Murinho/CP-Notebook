#include <bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define ld long double
#define fast                                                                   \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define PI 3.1415926535

using namespace std;

const ld EPS = 1e-6;
const ld pi = 3.1415926535;

struct Point {
    double x, y; //cambiar tipo de dato de acuerdo al problema
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
    ld magnitude(){ return sqrt((x*x) + (y*y)); } //longitud hipotenusa
    ld dot (const Point &b){ return (x * b.x) + (y * b.y); } //producto punto
    ld dist (const Point & b){ return (*this - b).magnitude(); } //distancia entre 2 puntos.
    ll cross(const Point& b, const Point& c) const { //Producto cruz
        ll cruz = (b - *this) * (c - *this);
        if (cruz < 0) return -1;
        if (cruz > 0) return +1;
        return 0;
    }
    ll determinant(const Point &b){ return (((*this).x) * b.y) - ((*this).y * b.x); } //determinante 2x2
    bool onSegment(Point p, Point r){ //checa si un punto esta en el segmento entre dos puntos (delimitado como si fuera un rectangulo)
        if ((*this).x <= max(p.x, r.x) && (*this).x >= min(p.x, r.x) && (*this).y <= max(p.y, r.y) && (*this).y >= min(p.y, r.y)) return true;

        return false;
    }
    double calculateAngle(){ //se calcula el angulo con respecto del eje 'x' y la ubicacion del punto
        Point pto = *this;
        double ca = pto.x;
        double hip = sqrt((pto.x*pto.x) + (pto.y*pto.y));
        double ang = acos(ca/hip);
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
                if(P1.cross(P2, P[i]) <= 0) break; //agregar (<=) si tambien se quieren incluir los puntos colineales sino solo (<)
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

signed main() {
    fast;
}