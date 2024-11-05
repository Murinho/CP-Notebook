const ll maxn = 5050;
const ll mod = 1e9+7;
const ll INF = 1e17;

struct Edge {
    ll a, b, cost;
};

vector <Edge> edges;
ll n,m,ncy[maxn];

void bford(int stnode){ //When wanting to find the longest path, invert the signs of the costs (+ -)
    vi d(n+1, 0LL);     //to find shortest paths from stnode: set to INF.
                        //to find any negative cycle in the graph, set to 0.
    //d[stnode] = 0;   <-- when having a starting node (task: find shortest paths), uncomment this.
    vi p(n+1, -1);
    int x = -1;
    fore(i,0,n){
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
        vi cycle;
        ll start = x;
        cycle.pb(x);
        x = p[x];
        while(start != x){
            cycle.pb(x);
            x = p[x];
        }
        cycle.pb(start);
        reverse(ALL(cycle));
        for(auto au : cycle) cout<<au<<" ";
        cout<<nl;
    }
}

void doit(){
    // insert edges first.
    bford(0); // from start node.
}