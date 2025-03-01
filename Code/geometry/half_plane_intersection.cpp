const ld eps = 1e-9, inf = 1e9; 

struct Halfplane { 
    Point p, pq; 
    ld angle;

	// IMPORTANT: Consider the left part of a vector as the inside part of the halfplane.
    Halfplane(const Point& a, const Point& b) : p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);    
    }

    bool out(const Point& r) { 
		Point ot = r-p;
		return (pq*ot) < -eps;
    }

    bool operator < (const Halfplane& e) const { 
        return angle < e.angle;
    } 

    friend Point inter(const Halfplane& s, const Halfplane& t) {
		Point ot = t.p - s.p;
        ld alpha = (ot*t.pq) / (s.pq*t.pq);
        return s.p + (s.pq * alpha);
    }
};

vector<Point> hp_intersect(vector<Halfplane>& H) { 
    Point box[4] = {  // Bounding box in CCW order
        Point(inf, inf), 
        Point(-inf, inf), 
        Point(-inf, -inf), 
        Point(inf, -inf) 
    };

    for(int i = 0; i<4; i++) { // Add bounding box half-planes.
        Halfplane aux(box[i], box[(i+1) % 4]);
        H.pb(aux);
    }

    // Sort by angle and start algorithm
    sort(ALL(H));
    deque<Halfplane> dq;
    int len = 0;
    for(int i = 0; i < sz(H); i++) {

        // Remove from the back of the deque while last half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
            dq.pop_back();
            --len;
        }

        // Remove from the front of the deque while first half-plane is redundant
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front();
            --len;
        }

        // Special case check: Parallel half-planes
        if (len > 0 && fabsl((H[i].pq*dq[len-1].pq)) < eps) {
            // Opposite parallel half-planes that ended up checked against each other.
            if (H[i].pq.dot(dq[len-1].pq) < 0.0) return vector<Point>();
            
            if (H[i].out(dq[len-1].p)){ // Same direction half-plane: keep only the leftmost half-plane.
                dq.pop_back();
                --len;
            }
            else continue;
        }

        // Add new half-plane
        dq.push_back(H[i]);
        ++len;
    }

    // Final cleanup: Check half-planes at the front against the back and vice-versa
    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front();
        --len;
    }

    // Report empty intersection if necessary
    if (len < 3) return vector<Point>();

    // Reconstruct the convex polygon from the remaining half-planes.
    vector<Point> pts;
    for(int i = 0; i < sz(dq); i++){
        int j = (i + 1) % sz(dq);
        pts.pb(inter(dq[i], dq[j]));
    }
    return pts;
}