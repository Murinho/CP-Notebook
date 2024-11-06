vector <Point> calculateHull(vector <Point> &p, int n){ //Calculo del Convex Hull
    if (n <= 2) return p;
    vector<Point> hull;
    int tam = 0;
    sort(ALL(p));
    fore(t,0,2){
        fore(i,0,n){
            while(sz(hull)-tam >= 2){
                Point p1 = hull[sz(hull)-2];
                Point p2 = hull[sz(hull)-1];
                //Producto cruz: P1 ---> P2 ---> P3 
                //agregar (<=) si tambien se quieren incluir los puntos colineales, sino solo (<)
                if(p1.cross(p2, p[i]) <= 0) break; 
                hull.pop_back();
            }
            hull.pb(p[i]);
        }
        hull.pop_back();
        tam = sz(hull);
        reverse(ALL(p));
    }
    return hull;
}
