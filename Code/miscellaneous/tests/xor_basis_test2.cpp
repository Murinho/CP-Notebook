// Tested with AC: https://acm.timus.ru/problem.aspx?space=1&num=1042
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
#define ppb pop_back
#define i128 __int128_t
#define ull unsigned long long
 
using namespace __gnu_pbds;
using namespace std;

static const ll B = 255;

struct XorBasis{
	vector < bitset <B> > xb,src;
	ll rank, added_cnt;
	vi p;
	
	XorBasis(): xb(B), src(B), rank(0), added_cnt(0) {}
	
	bool insert(bitset <B> x, ll idx) {
		added_cnt++;
		
		bitset <B> mrk;
		mrk[rank] = 1;

		for(int i = B - 1; i >= 0; i --) {
			if(x[i]) {
				if(xb[i].none()) {
					xb[i] = x;
					src[i] = mrk;
					p.pb(idx);
					rank++;
					return true;
				}else {
					x ^= xb[i];    
					mrk ^= src[i];
				}
			}
		}
		return false;
	}
	 
	pair < bitset <B>, bool> can_represent(bitset <B> x){
		bitset <B> ret;
		for(int i = B - 1; i >= 0; i --) {
			if (x[i]) {
			    if (xb[i].none()) return {ret, false};
			    ret ^= src[i];
			    x ^= xb[i];
			}
		}
		return {ret,true};
	}
	
	vi reconstruct(bitset <B> x){
		pair < bitset <B>, bool > aux = can_represent(x);
		if(aux.snd == false) return {}; // not possible to represent
		
		bitset <B> y = aux.fst;
		
		vi ret;
		fore(i,0,B){
			if (y[i]) ret.pb(p[i]);
		}
		
		return ret;
	}
};

ll n;

int main(){
    fast;
    cin >> n;
    XorBasis xb;
    fore(i,1,n+1){
    		ll x;
    		cin >> x;
    		bitset <B> bts;
    		while(x != -1){
    			bts[x-1] = 1;
    			cin >> x;
    		}
    		xb.insert(bts,i);
    }
    
    bitset <B> bts;
    fore(i,0,n) bts[i] = 1;
    
    vi v = xb.reconstruct(bts);
    
    if (!sz(v)){
    		cout << "No solution" << nl;
    }
    else{
    		sort(ALL(v));
    		for(auto &au : v) cout << au << " ";
    		cout << nl;
    }
    
    return 0;
}