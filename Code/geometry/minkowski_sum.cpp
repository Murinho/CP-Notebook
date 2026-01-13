// Compute Minkowski sum of two CONVEX polygons (remove collinear first)
// Returns answer in CCW order
void reorder_polygon(vector<Point> & P){
    int pos = 0;
    for(int i = 1; i < sz(P); i++){ 
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<Point> minkowski(vector<Point> P, vector<Point> Q){
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.pb(P[0]);
    P.pb(P[1]);
    Q.pb(Q[0]);
    Q.pb(Q[1]);

    vector<Point> result;
    int i = 0, j = 0;
    while(i < sz(P) - 2 || j < sz(Q) - 2){
        result.pb(P[i] + Q[j]);
        ll cross = (P[i + 1] - P[i]) * (Q[j + 1] - Q[j]); // cross product
        if(cross >= 0 && i < sz(P) - 2) i++;
        if(cross <= 0 && j < sz(Q) - 2) j++;
    }
    return result;
}