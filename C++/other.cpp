#pragma GCC optimize("O3")
/*(UNCOMMENT WHEN HAVING LOTS OF RECURSIONS)\
#pragma comment(linker, "/stack:200000000")
(UNCOMMENT WHEN NEEDED) */
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

// Custom comparator for set/map
struct comp {
	bool operator()(const double& a, const double& b) const {
		return a+EPS<b;}
};
set<double,comp> w; // or map<double,int,comp>

// double inf
const double DINF=numeric_limits<double>::infinity();