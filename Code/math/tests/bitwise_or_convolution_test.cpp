//Tested with: https://www.acmicpc.net/problem/25563
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

const ll mod = 998244353;

void subsetZetaTransform(vi &v){
    int n = sz(v); // n must be a power of 2.
    for(int j = 1; j<n; j <<= 1){
        fore(i,0,n){
            if (i&j) v[i] += v[i^j], v[i] %= mod;
        }
    }
}

void subsetMobiusTransform(vi &v){
    int n = sz(v); // n must be a power of 2.
    for(int j = 1; j<n; j <<= 1){
        fore(i,0,n){
            if (i&j) v[i] -= v[i^j], v[i] += mod, v[i] %= mod;
        }
    }
}

// c_k = Total sum where (i,j), i|j = k of a_i*b_j
vi orConvolution(vi a, vi b){
    subsetZetaTransform(a);
    subsetZetaTransform(b);
    fore(i,0,sz(a)) a[i] *= b[i], a[i] %= mod;
    subsetMobiusTransform(a);
    return a;
}

int main(){
    fast;
    ll n,k;
    cin>>n>>k;
    vi a(n,0ll),b(n,0ll);
    fore(i,0,n) cin>>a[i];
    fore(i,0,n) cin>>b[i];
    vi ans = (a,b);
    fore(i,0,sz(ans)) cout<<ans[i]<<" ";
    cout<<nl;
    return 0;
}