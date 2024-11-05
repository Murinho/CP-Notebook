//Tested with: https://cses.fi/problemset/task/1735/
//Lazy Segment Tree with set and add updates with sum get query.
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(int i=a;i<b;++i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define PI 3.1415926535
#define lsb(x) ((x)&(-x))
 
using namespace std;

const ll maxn = 2e5+100;
const ll mod = 1e9+7;
const ll lzneut = 0;
const ll neut = 0;

ll n,q;
vector <ll> a;

struct STree{
    vector <ll> st,lzadd,lzset; int n;
    STree(int n): st(4*n + 5,neut),lzadd(4*n + 5,0),lzset(4*n + 5,0), n(n){}

    void build(int node, int ini, int fin){
        if (ini == fin){
            st[node] = a[ini];
            return;
        }
        int mid = (ini+fin)/2;
        build(2*node,ini,mid);
        build(2*node + 1,mid+1,fin);
        st[node] = st[2*node] + st[2*node + 1];
    }

    void increment(int node, int ini, int fin, ll val){
        lzadd[node] += val;
        st[node] += (fin-ini+1)*val;
    }

    void assign(int node, int ini, int fin, ll val){
        lzset[node] = val;
        lzadd[node] = 0;
        st[node] = (fin-ini+1)*val;
    }   

    void push(int node, int ini, int fin){
        int mid = (ini+fin)/2;
        if (lzset[node]){
            assign(2*node,ini,mid,lzset[node]);
            assign(2*node + 1,mid+1,fin,lzset[node]);
            lzset[node] = 0;
        }
        if (lzadd[node]){
            increment(2*node,ini,mid,lzadd[node]);
            increment(2*node + 1,mid+1,fin,lzadd[node]);
            lzadd[node] = 0;
        }
    }

    void setUpdate(int node, int ini, int fin, int l, int r, ll val){
        if (fin < l || r < ini) return;
        if (l <= ini && fin <= r){
            assign(node,ini,fin,val);
            return;
        }
        push(node,ini,fin);
        ll mid = (ini+fin)/2;
        setUpdate(2*node,ini,mid,l,r,val);
        setUpdate(2*node + 1,mid+1,fin,l,r,val);
        st[node] = st[2*node] + st[2*node + 1];
    }

    void addUpdate(int node, int ini, int fin, int l, int r, ll val){
        if (fin < l || r < ini) return;
        if (l <= ini && fin <= r){
            increment(node,ini,fin,val);
            return;
        }
        push(node,ini,fin);
        ll mid = (ini+fin)/2;
        addUpdate(2*node,ini,mid,l,r,val);
        addUpdate(2*node + 1,mid+1,fin,l,r,val);
        st[node] = st[2*node] + st[2*node + 1];
    }

    ll query(int node, int ini, int fin, int l, int r){
        if (fin < l || r < ini) return neut;
        if (l <= ini && fin <= r){
            return st[node];
        }
        push(node,ini,fin);
        int mid = (ini+fin)/2;
        ll lsum = query(2*node,ini,mid,l,r);
        ll rsum = query(2*node + 1,mid+1,fin,l,r);
        st[node] = st[2*node] + st[2*node + 1];
        return lsum + rsum;
    }

    void build(){ build(1,1,n);}
    void setUpdate(int l, int r, ll val){ setUpdate(1,1,n,l,r,val);}
    void addUpdate(int l, int r, ll val){ addUpdate(1,1,n,l,r,val);}
    ll query(int l, int r){ return query(1,1,n,l,r);}
};

void init(){
    a.clear(), a.resize(n+1);
}


int main(){
    fast;
    cin>>n>>q;
    init();
    fore(i,1,n+1) cin>>a[i];

    STree st(n);
    st.build();
    while(q--){
        ll typ,l,r,x;
        cin>>typ>>l>>r;
        if (typ == 1){
            cin>>x;
            st.addUpdate(l,r,x);
        }
        else if (typ == 2){
            cin>>x;
            st.setUpdate(l,r,x);
        }
        else{
            cout<<st.query(l,r)<<nl;
        }
    }
}