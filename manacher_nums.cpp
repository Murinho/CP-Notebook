#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);

using namespace std;

ll tc,n,m,k,ans,best,d;
vector <ll> a,b;

void init(){
    ans = 0;
}

void manacher(){
    ll sz = a.size();
    ll l = 1, r = 1;
    b[0] = 1;
    b[sz-1] = 1;
    for (ll i = 1; i<sz-1; i++){
        b[i] = max(0LL, min(r-i, b[l + (r-i)]));
        while(a[i - b[i]] == a[i + b[i]]) b[i]++;
        
        if (i + b[i] > r){
            l = i - b[i], r = i + b[i];
        }
    }
}


int main(){
    fast;
    cin>>n;
    init();
    a.pb(0);
    for (int i = 1; i<=n; i++){
        ll num;
        cin>>num;
        a.pb(num);
        a.pb(0);
    }
    b.resize(a.size());
    manacher();
    for (auto au : b) cout<<au<<" ";
    cout<<nl;

    //Even positions denote odd palindromes.
    //Odd positions denote even palindromes.
    for (int i = 0; i<b.size(); i++){
        if (i%2 == 0){ //this is a '#' (counting even length palindromes).
            ans += (b[i]-1)/2;
        }
        else{ //this is an actual character (counting odd length palindromes).
            ans += b[i]/2;
        }
    }
    //new comment.
    cout<<ans<<nl;
    //esto es un nuevo comentario.
}