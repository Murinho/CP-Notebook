//Tested with: https://cses.fi/problemset/task/2133
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a; i<b; i++)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector <vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second

using namespace std;

struct dsu_save {
    int v, rnkv, u, rnku;
    
    dsu_save() {}
    dsu_save(int v, int rnkv, int u, int rnku)
        : v(v), rnkv(rnkv), u(u), rnku(rnku) {}
};

struct dsu_with_rollbacks {
    vi p, rnk;
    int comps;
    stack<dsu_save> op;

    dsu_with_rollbacks() {}
    dsu_with_rollbacks(int n) {
        p.resize(n);
        rnk.resize(n);
        fore(i,0,n){
            p[i] = i;
            rnk[i] = 0;
        }
        comps = n;
    }

    int find_set(int v){
        return (v == p[v]) ? v : find_set(p[v]);
    }
    bool unite(int v, int u){
        v = find_set(v);
        u = find_set(u);
        if (v == u) return false;
        comps--;
        if (rnk[v] > rnk[u]) swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        p[v] = u;
        if (rnk[u] == rnk[v]) rnk[u]++;
        return true;
    }
    void rollback(){
        if (op.empty()) return;
        dsu_save x = op.top();
        op.pop();
        comps++;
        p[x.v] = x.v;
        rnk[x.v] = x.rnkv;
        p[x.u] = x.u;
        rnk[x.u] = x.rnku;
    }
};

struct query {
    int v, u;
    bool united;
    query(int _v, int _u) : v(_v), u(_u) {}
};

struct QueryTree {
    vector<vector<query>> t;
    dsu_with_rollbacks dsu;
    int T;

    QueryTree() {}
    QueryTree(int T, int n) : T(T) {
        dsu = dsu_with_rollbacks(n);
        t.resize(4 * T + 4);
    }

    void add_to_tree(int v, int l, int r, int ul, int ur, query& q) {
        if (ul > ur)
            return;
        if (l == ul && r == ur) {
            t[v].pb(q);
            return;
        }
        int mid = (l+r)/2;
        add_to_tree(2 * v, l, mid, ul, min(ur, mid), q);
        add_to_tree(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
    }
    void add_query(query q, int l, int r) {
        add_to_tree(1, 0, T - 1, l, r, q);
    }
    void dfs(int v, int l, int r, vi& ans) {
        for (query& q : t[v]) {
            q.united = dsu.unite(q.v, q.u);
        }
        if (l == r)
            ans[l] = dsu.comps;
        else {
            int mid = (l + r) / 2;
            dfs(2 * v, l, mid, ans);
            dfs(2 * v + 1, mid + 1, r, ans);
        }
        for (query q : t[v]) {
            if (q.united) dsu.rollback();
        }
    }
    vi solve() {
        vi ans(T);
        dfs(1, 0, T - 1, ans);
        return ans;
    }
};

map < pii, ll > mp;
ll n,m,q;

int main(){
    fast;
    cin>>n>>m>>q;
    QueryTree qt(q+2,n+1); //queries and nodes are 0-indexed.
    fore(i,0,m){
        ll x,y;
        cin>>x>>y;
        x--, y--;
        if (x>y) swap(x,y);
        mp[{x,y}]=0; //save starting life index of the edge.
    }
    fore(i,1,q+1){
        ll t,x,y;
        cin>>t>>x>>y;
        x--, y--;
        if (x>y) swap(x,y);
        if (t == 1){ //create edge.
            mp[{x,y}]=i;
        }   
        else{ //delete edge.
            query qy(x,y);
            qt.add_query(qy,mp[{x,y}],i-1);
            mp.erase({x,y});
        }
    }
    //Add the end of the non-closed edges.
    for(auto au : mp){
        pii p = au.fst;
        int l = au.snd;
        query qy(p.fst,p.snd);
        qt.add_query(qy,l,q);
    }
    // Answer queries: amount of CCs at each moment i.
    vi ans = qt.solve();
    fore(i,0,q+1) cout<<ans[i]-1<<" ";
    cout<<nl;
    return 0;
}