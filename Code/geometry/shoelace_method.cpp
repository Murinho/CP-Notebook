#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

/*Shoelace method tested:
Link to the problem: https://codeforces.com/problemset/gymProblem/101845/D
Note: remove all the points that are collinear for it to work correctly (are standing between the line that connects other two points).
*/

struct Point{ double x,y; };

ll n,q;
vector <Point> poly;
vector <double> sum;
double best,totarea;
const int maxn = 2e5 + 10;

void init(){
	sum.resize(n+1);
	totarea = 0;
	best = 0;
	sum[0] = 0;
	poly.pb({0,0});
}

double cross(Point p1, Point p2){
	return ((p1.x*p2.y)-(p1.y*p2.x));
}

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	cin>>n>>q;
	init();
	for (int i = 1; i<=n; i++){
		double cx,cy;
		cin>>cx>>cy;
		Point po;
		po.x = cx;
		po.y = cy;
		poly.pb(po);
	}
	for (int i = 1; i<=n; i++){
		if (i == n) sum[i] = cross(poly[i],poly[1]);
		else sum[i] = cross(poly[i],poly[i+1]);
	}
	for (int i = 2; i<=n; i++) sum[i] += sum[i-1];
	//cout<<"\n"; 

	totarea = abs(sum[n])/2.0;
	//return 0;
	while(q--){
		double a,b;
		double ans;
		cin>>a>>b;
		if (a>b) swap(a,b);

		if (a+1 == b || (a == 1 && b == n)) continue;
		ans = sum[b-1]-sum[a-1];
		ans += cross(poly[b],poly[a]);
		ans = abs(ans)/2.0;
		ans = min(ans,totarea-ans);
		//cout<<ans<<"\n";
		best = max(best,ans);
	}
	cout<<fixed<<setprecision(6)<<best<<"\n";
	return 0;
}