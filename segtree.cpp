#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(int i=a; i<b; i++)
#define rofe(i,a,b) for(int i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector <vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second
#pragma GCC target("popcnt")
 
using namespace std;

const ll maxn = 2e5+10;

ll a[maxn];

struct STree{
    vi st; int n;
    STree(int n): st(4*n + 5),n(n){}

    void build(int node,int ini,int fin){
        if (ini == fin) { 
            st[node] = a[ini];
            return;
        }
        int mid = (ini+fin)/2;
        build(2*node,ini,mid); //Left sohn
        build(2*node + 1,mid+1,fin); //Right sohn
        st[node] = (st[2*node] + st[2*node + 1]); //desired operation
        return;
    }
    ll query(int node,int ini,int fin,int l,int r){
        if (l <= ini && fin <= r) return st[node]; //Fully in
        if (ini > r || fin < l) return 0; //Fully out
        int mid = (ini+fin)/2;
        return (query(2*node,ini,mid,l,r) + query(2*node + 1,mid+1,fin,l,r)); 
    }
    void upd(int node,int ini,int fin,int pos, ll val){
        if (fin < pos || pos < ini) return; //Fully out
        if (ini == fin && ini == pos) { 
            st[node] = val;
            return;
        }
        int mid = (ini+fin)/2;
        upd(2*node,ini,mid,pos,val);  
        upd(2*node + 1,mid+1,fin,pos,val); 
        st[node] = (st[2*node] + st[2*node + 1]);
        return;
    }
    void build(){ build(1,1,n);}
    void upd(int pos, ll val){ upd(1,1,n,pos,val);}
    ll query(int l, int r){ return query(1,1,n,l,r);}
};


int main(){
    fast;
}