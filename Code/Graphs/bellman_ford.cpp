#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
 
 
using namespace std;
 
const ll maxn = 5050;
const ll mod = 1e9+7;
const ll INF = 1e17;

struct Edge {
    ll a, b, cost;
};

vector <Edge> edges;
vector <ll> ncy;
ll n,m;


void init(){
    ncy.clear(), ncy.resize(n+1);
}

void bford(int stnode){ //When wanting to find the longest path, invert the signs of the costs (+ -)
    vector<ll> d(n+1, 0LL); //to find shortest paths from stnode: set to INF.
                            //to find any negative cycle in the graph, set to 0.
    //d[stnode] = 0;   <-- when having a starting node (task: find shortest paths), uncomment this.
    
    vector<ll> p(n+1, -1);
    int x = -1;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (Edge e : edges)
            if (d[e.a] < INF)
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = max(-INF, d[e.a] + e.cost);
                    p[e.b] = e.a; //to keep track of the path, pointing to the previous node. 
                    if (i+1 == n) ncy[e.b] = 1, x = e.b; //e.b is part of a negative cycle.
                }
    }
    if (x == -1) cout<<"No negative cycles"<<nl;
    else{
        cout<<"Negative cycle: "<<nl;
        fore(i,0,n) x = p[x];
        vector <int> cycle;
        ll start = x;
        cycle.pb(x);
        x = p[x];
        while(start != x){
            cycle.pb(x);
            x = p[x];
        }
        cycle.pb(start);
        reverse(cycle.begin(),cycle.end());
        for(auto au : cycle) cout<<au<<" ";
        cout<<nl;
    }
}


int main(){
    fast;
    cin>>n>>m;
    init();
    fore(i,0,m){
        ll x,y,z;
        cin>>x>>y>>z;
        edges.pb({x,y,z});
    }
    bford(0);
    return 0;
}