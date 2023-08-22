#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
typedef pair<ll,pi> pii;
const int N = 1e5+5;
ll n,m,ans[N];
bool vs[N];
vector<pi> g[N];

void prim(){
    //{Distancia,Costo,Nodo}.
    priority_queue<pii,vector<pii>,greater<pii> > pq;
    pq.push({0,{0,1}});
    while (!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        if (!vs[node.S.S]) {
            vs[node.S.S] = 1;
            ans[node.S.S] = node.S.F;
            ll z = node.F+1;
            for (auto u : g[node.S.S]) {
                pq.push({z,{u.S,u.F}});
            }
        }
    }
    ll q=0;
    for (int i=1;i<=n;i++) q +=ans[i];
    cout << q << "\n";
}

int main()
{
    //N: nodos, M: aristas.
    cin >>n >> m;
    for (int i=0;i<m;i++) {
        int a,b,c;
        cin >>a >> b >>c;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    prim();
    return 0;
}