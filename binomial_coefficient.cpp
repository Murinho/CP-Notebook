#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
 
using namespace std;

ll tc,n;
const ll maxn = 1e6 + 5;
const ll mod = 1e9+7;
const ll loga = 31;
vector <ll> f;
 
void precalc(){
    //Precalculate all the factorials:
    f.resize(maxn);
    f[0] = 1;
    fore(i,1,maxn) f[i] = (f[i-1]*i)%mod;
}
 
ll exponentiate(ll b, ll pw){
    ll expo = b;
    ll pot = 1;
    ll res = 1;
    for (int i = 1; i<=loga; i++){
        if ((pot | pw) == pw){
            res = (res*expo)%mod;
        }
        expo = (expo*expo)%mod;
        pot *= 2;
    }
    return res;
}

ll nCk(ll a, ll b){
    b = (f[b]*f[a-b])%mod;
    ll inverse = exponentiate(b,mod-2);
    ll res = (f[a]*inverse)%mod;
    return res;
}
 
int main(){
    fast;
    precalc();
    cin>>tc;
    while(tc--){
        ll a,b;
        cin>>a>>b; //a tomadas de a b.
        cout<<nCk(a,b)<<nl;
    }
    return 0;
}