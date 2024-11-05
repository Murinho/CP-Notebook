//Tested with: https://cses.fi/problemset/task/1190
//Maximum subarray sum in the array.
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
ll n,q;
vector <ll> a;

struct Node{
    ll max_sum,sumL,sumR,sum;
    Node operator+(Node b) {
        return {max(max(max_sum, b.max_sum), sumR + b.sumL),
                    max(sumL, sum + b.sumL), max(b.sumR, sumR + b.sum),
                    sum + b.sum};
    }
};

struct STree{
    vector <Node> st; int n;
    STree(int n): st(4*n + 5), n(n){}

    void build(int node, int ini, int fin){
        if (ini == fin){
            st[node] = {max(0ll, a[ini]), max(0ll, a[ini]), max(0ll, a[ini]), a[ini]};
            return;
        }
        int mid = (ini+fin)/2;
        build(2*node,ini,mid);
        build(2*node + 1,mid+1,fin);
        st[node] = st[2*node] + st[2*node + 1];
    }

    void update(int node, int ini, int fin, int pos, ll val){
        if (fin < pos || pos < ini) return;
        if (ini == fin && ini == pos){
            st[node] = {max(0ll, val), max(0ll, val), max(0ll, val), val};
            return;
        }
        ll mid = (ini+fin)/2;
        update(2*node,ini,mid,pos,val);
        update(2*node + 1,mid+1,fin,pos,val);
        st[node] = st[2*node] + st[2*node + 1];
    }

    void build(){ build(1,1,n);}
    void update(int pos, ll val){ update(1,1,n,pos,val);}
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
        ll x,y;
        cin>>x>>y;
        st.update(x,y);
        cout<<st.st[1].max_sum<<nl;
    }
}