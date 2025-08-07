// AC Tested with: https://cses.fi/problemset/task/2086
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

const ll maxn = 3015;
const ll inf = 1e18+7;

ll n,a[maxn],dp[maxn][maxn],psum[maxn],k;

void dnc(int i, int l, int r, int optl, int optr){
	if (l > r) return;
	
	int mid = (l+r)/2;
	pii best = {inf,-1};
	for(int j = optl; j < min(mid,optr+1); j++){
		ll sum = psum[mid] - psum[j];
		best = min(best, {dp[i-1][j] + (sum*sum), j});
	}
	
	dp[i][mid] = best.fst;
	int opt = best.snd;
	
	dnc(i,l,mid-1,optl,opt);
	dnc(i,mid+1,r,opt,optr);
}

int main(){
    fast;
    cin >> n >> k;
    fore(i,1,n+1){
    	cin >> a[i];
    	psum[i] = psum[i-1] + a[i];
    }
    
    fore(i,1,n+1) dp[0][i] = inf;
    dp[0][0] = 0;
    
    fore(i,1,k+1){
    	dnc(i,1,n,0,n-1);
    }
    
    cout << dp[k][n] << nl;
    return 0;
}