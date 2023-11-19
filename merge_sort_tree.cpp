//Tested with: https://codeforces.com/contest/1899/problem/G
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define ALL(s) s.begin(),s.end()
#define vi vector <ll>
#define vvi vector<vi>
#define PI 3.1415926535
    
    
using namespace std;

const ll INF = 1e17;
const ll maxn = 1e5+100;

ll tc,n,qys,p[maxn],sta[maxn],en[maxn],cont;
vector < vector <ll> > adj;


void init(){
    adj.clear(), adj.resize(n+1);
    cont = 0;
}


void dfs(int anode, int node){
    cont++;
    sta[node] = cont;
    for(auto au : adj[node]){
        if (anode != au) dfs(node,au);
    }
    en[node] = cont;
}

struct Node{
    vector <ll> v;
    void order(){
        sort(ALL(v));
    }
    int get(int val_l, int val_r){ //nos interesa saber si al menos hay 1 elemento en el rango [val_l, val_r]
        int sz = v.size();
        if (val_r < v[0] || v[sz-1] < val_l) return 0;
        //find the lower bound.
        int l = 0;
        int r = sz-1;
        while(l < r){
            int mid = (l+r)/2;
            if (val_l <= v[mid]) r = mid;
            else l = mid+1;

            if (l+1 == r){
                if (val_l <= v[l]) r = l;
                break;
            }

        }
        int lwb = r;
        //find the upper bound.
        l = 0;
        r = sz-1;
        while(l < r){
            int mid = (l+r)/2;
            if (v[mid] <= val_r) l = mid;
            else r = mid-1;

            if (l+1 == r){
                if (v[r] <= val_r) l = r;
                break;
            }
        }
        int hgb = l;
        if (hgb-lwb+1 > 0) return 1; 
        return 0;
    }
};

struct MSTree{
    vector <Node> st; int n;
    MSTree(int n): st(4*n + 5), n(n) {}
    void upd(int node, int ini, int fin, int pos, int val){
        st[node].v.pb(val);
        if (ini == fin) return;
        int mid = (ini+fin)/2;
        if (pos <= mid) upd(2*node,ini,mid,pos,val);
        else upd(2*node + 1,mid+1,fin,pos,val);
    }
    int query(int node, int ini, int fin, int l, int r, int val_l, int val_r){
        if (fin < l || r < ini) return 0;
        if (l <= ini && fin <= r) return st[node].get(val_l,val_r);
        int mid = (ini+fin)/2;
        return (query(2*node,ini,mid,l,r,val_l,val_r)|query(2*node + 1,mid+1,fin,l,r,val_l,val_r));
    }
    void order(){ fore( i,1,4*n + 5) st[i].order();} //ordenar todos los arreglos de todos los nodos.
    void upd(int pos, int val){ upd(1,1,n,pos,val);}
    int query(int l, int r, int val_l, int val_r){ return query(1,1,n,l,r,val_l,val_r);}
};

int main(){
    fast;
	cin>>tc;
    while(tc--){
        cin>>n>>qys;
        init();
        fore(i,1,n){
            ll x,y;
            cin>>x>>y;
            adj[x].pb(y);
            adj[y].pb(x);
        }
        dfs(1,1);
        MSTree st(n);

        fore(i,1,n+1) cin>>p[i], st.upd(i,sta[p[i]]);

        st.order(); //despues de insertar todos los valores dentro del Merge Sort tree, hay que ordenar todos los nodos (sus arreglos internos).
        while(qys--){
            ll l,r,x;
            cin>>l>>r>>x;
            if (st.query(l,r,sta[x],en[x])) cout<<"YES"<<nl;
            else cout<<"NO"<<nl;
        }   
        cout<<nl;
    }
    return 0;
}