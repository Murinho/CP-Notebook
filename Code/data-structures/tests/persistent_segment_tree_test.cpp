// SPOJ: Kquery. AC
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define rofe(i,a,b) for(ll i=a-1;i>=b;--i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define lsbpos(x) __builtin_ffs(x)
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second
#pragma GCC target("popcnt")
 
using namespace __gnu_pbds;
using namespace std;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int,null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;\

const ll maxn = 2e6+10;

struct Vertex {
    Vertex *l, *r;
    ll sum;

    Vertex(ll val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

vi uni;

Vertex* build(int tl, int tr) {
    if (tl == tr)
        return new Vertex(0);
    int tm = (tl + tr) / 2;
    return new Vertex(build(tl, tm), build(tm+1, tr));
}

/*
int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
} */

int query(Vertex *v, int tl, int tr, ll k){
	int vl = uni[tl];
	int vr = uni[tr];
	if (tl == tr){
		if (k < vl) return v->sum;
		else return 0;
	}
	if (vr <= k) return 0; //all numbers are smaller or equal than k.
	if (k < vl) return v->sum;
	int mid = (tl+tr)/2;
	return query(v->l,tl,mid,k) + query(v->r,mid+1,tr,k);
}

Vertex * update(Vertex *v, int tl, int tr, int pos, ll val){
	if (tl == tr){
		return new Vertex(v->sum + val);
	}
	int mid= (tl+tr)/2;
	if (pos <= mid) return new Vertex(update(v->l, tl, mid, pos, val), v->r);
    return new Vertex(v->l, update(v->r,mid+1, tr, pos, val));
}

/*
Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new Vertex(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos, new_val));
} */

Vertex *ve[maxn];
ll n;
ll a[maxn];
ll q;
map <ll,ll> mp;

int main(){
    fast;
	cin>>n;
	uni.pb(0);
	fore(i,1,n+1){
		cin>>a[i];
		uni.pb(a[i]);
	}
	
	sort(ALL(uni));
	uni.erase(unique(ALL(uni)),uni.end());
	
	fore(i,0,sz(uni)) mp[uni[i]]=i;
	
	ve[0]=build(0,sz(uni)-1);
	fore(i,1,n+1){
		ve[i]=update(ve[i-1],0,sz(uni)-1,mp[a[i]],1);
	}
		
	cin>>q;
	while(q--){
		ll l,r,k;
		cin>>l>>r>>k;
		ll ans = query(ve[r],0,sz(uni)-1,k) - query(ve[l-1],0,sz(uni)-1,k);
		cout<<ans<<nl;
	}
	return 0;
}