//Tested with: https://codeforces.com/gym/104758/problem/B
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
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)

using namespace std;

const ll mod = 1e9+7;
ll tc,n,m,k;

vvi mul(vvi a, vvi b) {
    vvi c(sz(a), vi(sz(b[0])));
    for (int i = 0; i < sz(a); i++) 
        for (int j = 0; j < sz(b); j++)
            for ( int k = 0; k < sz(a); k++) 
                (c[i][j] += a[i][k]*b[k][j]%mod)%=mod; 
    return c;
}

vvi exp( vvi x, ll y) {
    vvi r(sz(x), vi(sz(x)));
    bool flag = false;
    while (y>0){
        if (y&1) {
            if (!flag) r = x, flag = true;
            else r = mul(r,x);
        }
        y=y>>1;
        x = mul(x,x);
    }
    return r;
}

int main(){
    fast;
    cin>>k;
    if (k < 4){
        if (k == 0) cout<<1<<nl;
        else if (k == 1) cout<<2<<nl;
        else if (k == 2) cout<<3<<nl;
        else cout<<17<<nl;
        return 0;
    }
    k -= 2ll; // Adjusting for the additional constant term
    vvi mat;
    mat.resize(4);
    //Function: F(n) = 3*F(n-1) + 2*F(n-2) + F(n-3) + 3.
    mat[0] = {3,2,1,3}; 
    mat[1] = {1,0,0,0}; 
    mat[2] = {0,1,0,0}; 
    mat[3] = {0,0,0,1}; //to keep the +3 constant.

    vi iniv = {3,2,1,1}; //Initial vector.

    mat = exp(mat,k);
    ll ans = 0;
    fore(i,0,4){
        ll aux = (mat[0][i]*iniv[i])%mod;
        ans = (ans + aux)%mod;
    }
    cout<<ans<<nl;
    return 0;
}
