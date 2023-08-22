#include<bits/stdc++.h>
using namespace std;

#define nl '\n'
#define P complex<ll>
#define X real()
#define Y imag()
#define pb push_back
#define ll long long

int colins = 0,points_amount = 0;

int cross(P &a, P &b, P &c) {
    P u = c - b;
    P v = a - b;
    ll cp = (conj(u) * v).Y;
    return (cp > 0) - (cp < 0);
}

vector<P> hull(vector<P> &v) {
    vector<P> ans = {v[0]};
    for (int i = 1; i < v.size(); i++) {
        while (ans.size() > 1) {
            P b = ans.back();
            ans.pop_back();
            P a = ans.back();
            P c = v[i];
            int res = cross(a,b,c);
            if (res == -1) {
                ans.push_back(b);
                break;
            }
            if (res == 0) colins++;
        }
        ans.push_back(v[i]);
    }
    return ans;
}

bool checkInside(P point, vector<P> polygon) {
    int count = 0;
    int n = polygon.size();
    if (n < 3) return false;
    //Edit this:
    if (n == 3){
        if (n + (points_amount - n - colins) < 4) return false;
    }

    for (int i = 0; i < n; i++) {
        const P p1 = polygon[i];
        const P p2 = polygon[(i + 1) % n];

        // Check if the point lies on the edge of the polygon
        if ((p1.Y == point.Y && p2.Y == point.Y) ||
            (point.Y > std::min(p1.Y, p2.Y) && point.Y <= std::max(p1.Y, p2.Y))) {
            double intersectX = p1.X + (point.Y - p1.Y) * (p2.X - p1.X) / (p2.Y - p1.Y);

            if ((double)point.X <= intersectX)
                count++;
        }
    }
    return (count&1);
}


signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    
    int n,m,ans = 0; 
    cin >> n;
    points_amount = n;
    colins = 0;
    vector<P> v;
    for (int i = 0; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        v.pb({x,y});
    }
    sort(v.begin(), v.end(), 
         [] (const P &a, const P &b) {
                return (a.X == b.X) ? (a.Y < b.Y) : (a.X < b.X);
        });
    vector<P> v1 = hull(v);

    sort(v.begin(), v.end(),
         [] (const P &a, const P &b) {
                return (a.X == b.X) ? (a.Y > b.Y) : (a.X > b.X);
        });
    vector<P> v2 = hull(v);
    for (int i = 1; i < v2.size(); i++) {
        if (v2[i] == v1[0]) break;
        v1.push_back(v2[i]);
    }
    /*
    cout<<"Convex Hull is: "<<nl;
    for (auto i : convhull) cout<<i.X<<" "<<i.Y<<nl;
    cout<<"---------"<<nl; */
    cin>>m;

    //How to tell if a point is inside a polygon or not given the polygon.
    for (int i = 1; i<=m; i++){
        int x,y;
        P punto;
        cin>>x>>y;
        punto = {x,y};
        if (checkInside(punto,v1)){
            ans++;
            //cout<<"Inside: "<<x<<" "<<y<<nl;
        }
    }
    cout<<ans<<nl;
    return 0;
}