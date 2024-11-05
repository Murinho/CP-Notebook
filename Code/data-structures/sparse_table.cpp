//Tested with: https://codeforces.com/contest/872/problem/B
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((int)a.size())
#define PI 3.1415926535
#define lsb(x) ((x)&(-x))
 
using namespace std;

const ll maxn = 2e5+500;
const ll INF = 1e18;
const ll loga = 22;
ll n,k,sp[maxn][loga],a[maxn],mx = -INF, ans = -INF, mn = INF;

ll queryMin(int l, int r){
	//Check in steps of powers of 2.
	int tam = (r-l+1);
	ll res = INF;
	for(int i = loga-1; i>=0; i--){
		if (((1ll<<i)&tam) == (1ll<<i)){
			res = min(res,sp[l][i]);
			l += (1ll<<i);
		}
	}
	return res;
}

void solve(){
	//Create sparse table.
	for(int i = 1; i<loga; i++){
		for(int j = 1; j<=n; j++){
			if (j + (1ll<<i) - 1 <= n) sp[j][i] = min(sp[j][i-1], sp[j + (1ll<<(i-1))][i-1]); //left and right parts.
		}
	}
		
	//Query for each possible prefix and suffix:
	for(int i = 1; i<n; i++){
		ans = max(ans,max(queryMin(1,i),queryMin(i+1,n)));
	}
	cout<<ans<<nl;
}

int main(){
    fast;
	cin>>n>>k;
	fore(i,1,n+1){
		cin>>a[i];
		mn = min(mn,a[i]);
		mx = max(mx,a[i]);
		sp[i][0] = a[i]; //add to the sparse table.
	}

	if (k == 1) cout<<mn<<nl;
	else if (k >= 3) cout<<mx<<nl;
	else solve(); //use sparse table.
	return 0;
}