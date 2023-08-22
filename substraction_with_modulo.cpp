#include<bits/stdc++.h>
using namespace std;

#define nl '\n'
#define pb push_back
#define ll long long
#define fast cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);

ll tc,n,ans;
const ll maxn = 1e6;
const ll mod = 1e9+7;
ll fact[maxn+5];

int main(){
    fast;
    cin>>n;
    fact[0] = 1;  
    ll pot = 1;
    for (ll i = 1; i<=n; i++) fact[i] = (fact[i-1]*i)%mod;
    for (ll i = 1; i<n; i++) pot *= 2;
    cout<<(fact[n]-pot+mod)%mod<<nl;
    return 0;
}