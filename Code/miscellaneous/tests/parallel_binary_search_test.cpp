// AC: https://www.spoj.com/problems/METEORS/
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
#define eb emplace_back
#pragma GCC target("popcnt")
 
using namespace __gnu_pbds;
using namespace std;
 
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int,null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;
 
const ll maxn = 3e5+10;
const ll loga = 21;
 
struct Qu{
	ll l,r,val;
};
 
ll n,m,fen[maxn];
 
// Sum of values. (1-indexed).
void add(int x, ll v){
    while (x <= m+1){
        fen[x] += v;
        x += lsb(x);
    }
}
// Getting to whole prefix.
ll get(int x){ 
    ll freq = 0;
    while (x > 0){
        freq += fen[x];
        x -= lsb(x);
    }
    return freq;
}
 
void clean_fen(){
	fore(i,0,m+1) fen[i]=0;
}
 
void apply(int l, int r, ll val){
	if (l <= r){
		add(l,val), add(r+1,-val);
	}
	else{
		add(1,val), add(r+1,-val);
		add(l,val);
	}
}
 
ll a[maxn],q,b[maxn],cnt[maxn];
ll l[maxn],r[maxn]; //keep left and right for each country.
Qu qs[maxn];
vi belong[maxn],tocheck[maxn];
 
int main(){
    fast;
	cin>>n>>m;
	fore(i,1,m+1){ //segment belonging to which country.
		cin>>a[i];
		belong[a[i]].eb(i);
	}
	
	fore(i,1,n+1){ //requirements of each country.
		cin>>b[i];
	}
	
	cin>>q;
	fore(i,1,q+1){
		cin>>qs[i].l>>qs[i].r>>qs[i].val;
	}
	
	fore(i,1,n+1){
		l[i]=1, r[i]=q+1; //Init left and right for each country.
	}
	
	// Do parallel binary search:
	bool changed=true;
	while(changed){
		changed=false;
		clean_fen();
		fore(i,1,n+1){
			if (l[i] != r[i]) tocheck[(l[i] + r[i]) >> 1].pb(i);
		}
		fore(i,1,q+1){
			apply(qs[i].l,qs[i].r,qs[i].val);
			while(sz(tocheck[i])){
				changed=true;
				int id = tocheck[i].back();
				tocheck[i].pop_back();
				
				ll sum=0;
				for(auto sec : belong[id]){
					sum += get(sec);
					if (sum >= b[id]) break;
				}
				if (sum >= b[id]) r[id]=i;
				else l[id]=i+1;
			}
		}
	}
	// print answer for each country:
	fore(country,1,n+1){
		if (l[country] <= q) cout<<l[country]<<nl;
		else cout<<"NIE"<<nl;
	}
	return 0;
	
} 