//Tested with: https://www.spoj.com/problems/ACQUIRE/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((int)a.size())
#define PI 3.1415926535
#define lsb(x) ((x)&(-x))
 
using namespace std;

const ll maxn = 5e4+100;
const ll INF = 1e17;

struct Rectangle{
    ll w,h;
};

ll n,dp[maxn];
vector <Rectangle> a;

bool cmp(Rectangle r1, Rectangle r2){
    if (r1.h == r2.h) return r1.w < r2.w;
    return r1.h < r2.h;
}

struct CHT { //For Optimizing DPs that can be modeled as y = mx + b.
    //This code is made to find the minimums. Maximums can also be found.
    //Use When slopes are in decreasing order: m1 > m2 > ... > mk
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

void init(){
    fore(i,0,n+1) dp[i] = INF;
}

int main(){
    fast;
    cin>>n;
    init();
    fore(i,0,n){
        ll w,h;
        cin>>w>>h;
        a.pb({w,h});
    }
    sort(ALL(a),cmp);
    ll cnt = 1;
    ll pos = n-1;
    for(int i = n-2; i>=0; i--){
        if (a[i].w <= a[pos].w || a[i].h >= a[pos].h){
            a[i].w=a[i].h=0;
        }
        else{
            cnt++;
            pos = i;
        }
    }
    CHT cht;
    ll idx = 1;
    dp[0] = 0;
    fore(i,0,n){
        if (a[i].h == 0) continue;
        cht.insert(a[i].w,dp[idx-1]);
        dp[idx] = cht.query(a[i].h);
        idx++;
    }   
    cout<<dp[cnt]<<nl;
    return 0;
}