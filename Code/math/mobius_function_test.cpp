//Tested with: https://www.spoj.com/problems/SQFREE/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a; i<b; i++)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector <vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second

using namespace std;

const ll maxn = 1e7+1;

ll mobius[maxn],sum[maxn];

/* Mobius function: mu(n)
    mu(n) = 1, if n = 1.
    mu(n) = 0, if n has a squared prime factor.
    mu(n) = (-1)^k, if n is a product of k distinct prime factors.
*/

void computeMobius(){
    mobius[1] = -1;
    for (int i = 1; i < maxn; i++) {
        if (mobius[i]) {
            mobius[i] = -mobius[i];
            for (int j = 2 * i; j < maxn; j += i) { mobius[j] += mobius[i]; }
        }
    }
}

void solve(){ // Number of square free numbers in the range of [1,n]
    ll n,ans=0;
    cin>>n;
    for(ll i = 1; 1ll * i * i <= n; i++){
        ans += (mobius[i]*n)/(i*i);
    }
    cout<<ans<<nl;
    return;
}


int main(){ 
    fast;
    ll tc;
    cin>>tc;
    computeMobius();
    while(tc--){solve();}
}