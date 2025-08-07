// AC Tested with: https://www.spoj.com/problems/BRKSTRNG/
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
 
using namespace __gnu_pbds;
using namespace std;

const ll maxn = 1010;
const ll inf = 1e18;
ll n,m,dp[maxn][maxn],a[maxn],opt[maxn][maxn];

void init(){
	a[0] = 0;
	a[m+1] = n;
	fore(i,0,m+2){
		fore(j,i,m+2){
			dp[i][j] = inf;
		}
	}
	fore(i,0,m+2){
		dp[i][i] = 0;
		dp[i][i+1] = 0;
		opt[i][i] = i;
		opt[i][i+1] = i+1;
	}
}

ll f(ll i, ll j){
	return a[j] - a[i];
}

void solve(){
	init();
	fore(i,1,m+1) cin >> a[i];
	
	for(ll i = m+1; i>=0; i--){
		for(ll j = i+2; j <= m+1; j++){
			ll mn = inf;
			ll cost = f(i,j);
			for (ll k = opt[i][j-1]; k <= min(j, opt[i+1][j]); k++) {
                if (mn >= dp[i][k] + dp[k][j] + cost) {
                    opt[i][j] = k; 
                    mn = dp[i][k] + dp[k][j] + cost; 
                }
            }
            dp[i][j] = mn;
		}
	}
	cout << dp[0][m+1] << nl;
	return;
}

int main(){
    fast;
    while(cin>>n>>m){
        solve();
    }
    return 0;
}