#include <bits/stdc++.h>
#define ll long long
#define pb push_back
 
using namespace std;
 
ll tc,n;
const ll maxn = 1e6 + 5;
const ll mod = 1e9+5; //mod = mod2 - 2;
const ll mod2 = 1e9+7;
vector <ll> f;
 
void precalc(){
    //Precalculate all the factorials:
    f.resize(maxn);
    ll fact = 1;
    f[0] = 1;
    for (int i = 1; i<maxn-4; i++){
        f[i] = fact;
        fact = ((fact*(i+1))%mod2)%mod2;
    }
}
 
ll exponentiate(ll b){
    ll expo = b;
    ll pot = 1;
    ll ans = 1;
    for (int i = 1; i<=31; i++){
        if ((pot | mod) == mod){
            ans = (ans*expo)%mod2;
        }
        expo = (expo*expo)%mod2;
        pot *= 2;
    }
    return ans;
}
 
int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    precalc();
    cin>>tc;
    while(tc--){
        ll a,b;
        cin>>a>>b; //a tomadas de a b.
        b = (f[b]*f[a-b])%mod2;
        ll inverse = exponentiate(b);
        cout<<(f[a]*inverse)%mod2<<"\n";
    }
    return 0;
}