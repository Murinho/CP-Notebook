//Tested with: https://cses.fi/problemset/task/1654
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
    
using namespace std;

const ll maxbit = 20;
const ll maxn = 1<<20;

ll dp[maxn][maxbit]; //{mask,last bit}
ll sos[maxn][2],bucket[maxn],n,a[maxn],inbucket[maxn];

int main() {
	fast;
	cin>>n;
	fore(i,0,n){
		cin>>a[i];
		bucket[a[i]]++;
		inbucket[maxn-1-a[i]]++;
	}
	//X OR Y = X
	fore(mask,0,maxn){
		dp[mask][0] = bucket[mask];
		fore(x,0,maxbit){
			dp[mask][x+1] = dp[mask][x];
			if (mask & (1<<x)){
				dp[mask][x+1] += dp[mask - (1ll<<x)][x];
			}
		}
		sos[mask][0] = dp[mask][maxbit];
	}

	//X OR Y = X inverse:
	fore(mask,0,maxn){
		dp[mask][0] = inbucket[mask];
		fore(x,0,maxbit){
			dp[mask][x+1] = dp[mask][x];
			if (mask & (1<<x)){
				dp[mask][x+1] += dp[mask - (1ll<<x)][x];
			}
		}
		sos[mask][1] = dp[mask][maxbit];
	}

	//Answer:
	fore(i,0,n){
		//X OR Y = X, X AND Y = X, X AND Y != 0
		cout<<sos[a[i]][0]<<" "<<sos[maxn-1-a[i]][1]<<" "<<n-sos[maxn-1-a[i]][0]<<" ";
		cout<<nl;
	}
	return 0;
}