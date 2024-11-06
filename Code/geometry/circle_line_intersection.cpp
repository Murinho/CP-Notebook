vector <Point> circleLineIntersection(double a, double b, double c, double r){ 
    //Dados los coeficientes de la ecuacion de la recta y el radio del circulo con centro en el origen
    vector <Point> pts;
    double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)+EPS){} // 0 points.
    else if (abs (c*c - r*r*(a*a+b*b)) < EPS) pts.pb({x0,y0}); // 1 point.
    else{ // 2 points.
        double d = r*r - c*c/(a*a+b*b);
        double mult = sqrt (d / (a*a+b*b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        pts.pb({ax,ay});
        pts.pb({bx,by});
    }
    return pts;
}