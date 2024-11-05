const ll INF = 1e18;
const ll maxn = 2e5+5;
ll n,m,d[maxn];
vector <pii> adj[maxn]; //{adjacent node,cost}

void daikra(int stnode){
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    d[stnode]=0;
    pq.push({d[stnode],stnode});
    while(!pq.empty()){
        ll curw = pq.top().fst;
        ll node = pq.top().snd;
        pq.pop();
        if (curw != d[node]) continue;
        for(auto au : adj[node]){
            int signode = au.fst;
            ll sigw = au.snd;
            if (d[signode] > d[node] + sigw){
                d[signode] = d[node] + sigw;
                pq.push({d[signode],signode});
            }
        }
    }
}