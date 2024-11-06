ld getPolygonArea(vector <Point> poly){ //Calculo de area de poligono
    ll ans = 0;
    poly.pb(poly.front());
    fore(i,1,sz(poly)) ans += (poly[i-1]*poly[i]);
    return abs(ans)/2.0;
}