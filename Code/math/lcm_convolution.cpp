//Tested with: https://judge.yosupo.jp/problem/lcm_convolution
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

vi primeEnumerate(int n){ //Linear sieve.
    vi p;
    vector <bool> b(n+1,1);
    fore(i,2,n+1){
        if (b[i]) p.pb(i);
        for(int j : p){
            if (i*j>n) break;
            b[i*j]=0;
            if (i%j == 0) break;
        }
    }
    return p;
}

void divisorZetaTransform(vi &v){
    const int n = sz(v)-1;
    for(int p : primeEnumerate(n)){
        for (int i = 1; i*p <= n; i++){
            v[i*p] = (v[i*p]+v[i])%mod;
        }
    }
}

void divisorMobiusTransform(vi &v){
    const int n = sz(v)-1;
    for(int p : primeEnumerate(n)){
        for(int i = n/p; i; i--){
            v[i*p] = (v[i*p]-v[i]+mod)%mod;
        }
    }
}

// c_k = TotalSum where lcm(i,j)=k of a_i*b_j modulo mod.
vi lcmConvolution(vi a, vi b){
    divisorZetaTransform(a);
    divisorZetaTransform(b);
    fore(i,0,sz(a)) a[i] = (a[i]*b[i])%mod;
    divisorMobiusTransform(a);
    return a;
}

int main(){
    fast;
    ll n;
    cin>>n;
    vi a(n+1,0),b(n+1,0);
    fore(i,1,n+1) cin>>a[i];
    fore(i,1,n+1) cin>>b[i];

    vi ans = lcmConvolution(a,b);
    fore(i,1,n+1) cout<<ans[i]<<" ";
    cout<<nl;
    return 0;
}