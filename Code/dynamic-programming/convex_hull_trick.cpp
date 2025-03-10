const ll maxn = 1e5+5;

struct CHT { //For Optimizing DPs that can be modeled as y = mx + b.
    //This code is made to find the minimums. Maximums can also be found.
    //Use When slopes are in decreasing order for minimums: m1 > m2 > ... > mk
	//Use when slopes are in increasing order for maximums: m1 < m2 < ... < mk
    struct Line {
        ll slope, yIntercept;
 
        Line(ll slope, ll yIntercept) : slope(slope), yIntercept(yIntercept) {}
 
        ll val(ll x) {
            return slope * x + yIntercept;
        }
 
        ll intersect(Line y) {
            return (y.yIntercept - yIntercept + slope - y.slope - 1) / (slope - y.slope);
        }
    };
 
    deque<pair<Line, ll>> dq;
 
    void insert(ll slope, ll yIntercept) {
        Line newLine(slope, yIntercept);
 
        //Pop lines until all lines become useful. Popping the lines that become irrelevant.
		// For minimums >=
		// For maximums <= 
        while (!dq.empty() && dq.back().second >= dq.back().first.intersect(newLine)) dq.pop_back();
            
 
        if (dq.empty()) {
            dq.emplace_back(newLine, 0);
            return;
        }
 
        dq.emplace_back(newLine, dq.back().first.intersect(newLine));
    }
 
    ll query(ll x) { //When x values are given in ascending order: x1 < x2 < .. xk.
        //Just need to use a deque, no need to use Binary Search.
        while (sz(dq) > 1) {
            if (dq[1].second <= x) dq.pop_front();
            else break;
        }
 
        return dq[0].first.val(x);
    }
 
    ll query2(ll x) { //Use Binary Search when x values are given without a specific order.
        auto qry = *lower_bound(dq.rbegin(), dq.rend(),
                                make_pair(Line(0, 0), x),
                                [&](const pair<Line, ll> &a, const pair<Line, ll> &b) {
                                    return a.second > b.second;
                                });
 
        return qry.first.val(x);
    }
};

ll dp[maxn],a[maxn],b[maxn];

void doit(){
    CHT cht;
    cht.insert(b[1],dp[1]); //slope and yIntercept.
    dp[2] = cht.query(a[2]);
    //...
}