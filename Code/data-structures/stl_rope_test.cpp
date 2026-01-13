// Tested with AC: https://www.spoj.com/problems/AROPE/
#include <bits/stdc++.h>
#include <ext/rope>
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
 
using namespace std;
using namespace __gnu_cxx;

string s;
ll q;
rope <char> rp; // 0-indexed.

int main(){
    fast;
   	cin >> s;
   	for(auto &au : s){
   		rp.pb(au);
   	}
   	
   	cin >> q;
   	while(q--){
   		ll t,x,y;
   		cin >> t;
   		if (t == 1){
   			cin >> x >> y;
   			rope<char> sub = rp.substr(x, y-x+1);
   			rp.erase(x, y-x+1);
   			sub += rp;
   			swap(sub,rp);
   		}
   		else if (t == 2){
   			cin >> x >> y;
   			rope <char> sub = rp.substr(x,y-x+1);
   			rp.erase(x, y-x+1);
   			rp += sub;
   		}
   		else{
   			cin >> x;
   			cout << rp[x] << nl;
   		}
   	}
   	
    return 0;
}