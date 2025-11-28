/*
Classic problem:
Consider the following problem. There are n cities. You want 
to travel from city 1 to city n by car. To do this you have to buy 
some gasoline. It is known that a liter of gasoline costs cost[k] 
in the k-th city. Initially your fuel tank is empty and you spend 
one liter of gasoline per kilometer. Cities are located on the 
same line in ascending order with k-th city having coordinate x[k].
Also you have to pay toll[k] to enter k-th city. 

Recurrence:
dp[i] = toll[i] + fore(j,0,i) min(cost[j]*(x[i]-x[j]) + dp[j])

Model problem as lines: M = Ax + B

For constant B group all constants or variables that depend
only on themselves.
*/


struct Line{
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};
 
struct LineContainer : multiset<Line, less<>>{ // For Max values
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	// For Min values use: cht.add(-k,-m) and -cht.query(x);
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p > y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};