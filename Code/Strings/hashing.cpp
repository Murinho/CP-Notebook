#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

const ll maxn = 1e6 + 5;
const ll M = 1e9+9; //this one should be a prime number.
const ll B = 131;
string s,t;
ll tams,tamt,hasht,ans;

vector <ll> pws,h;

ll conv(char c){
    return (c-'a'+1);
}

void clean(){
    tams = s.size();
    tamt = t.size();
    pws.clear();
    pws.resize(maxn);
    h.clear();
    h.resize(maxn);
    pws[0] = 1;
    h[0] = conv(s[0]);
    hasht = ans = 0;
}

int main(){ //Note: to query the hashing of a substring it should be: r = start + length, l = r - length
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin>>s;
    cin>>t;
    clean();
    for (int i = 1; i<maxn-3; i++){
        pws[i] = (B * pws[i-1])%M;
    }
    for (int i = 0; i<tams; i++){
        h[i+1] = ((h[i]*B)+conv(s[i]))%M;
    }
    //calculate the hash number for target string:
    for (int i = 0; i<tamt; i++){
        hasht = ((hasht*B)+conv(t[i]))%M;
    }
    //For all possible substrings, check if hashings of substring 's' and 't' are equal:
    for (int i = tamt; i<=tams; i++){
        ll aux = (h[i]-h[i-tamt]*pws[tamt]%M + M)%M;
        if (aux == hasht) ans++;
    }
    cout<<ans<<"\n";
}