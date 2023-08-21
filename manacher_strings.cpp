#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);

using namespace std;

ll tc,n,m,k,best,pos,target,ind,cont;
vector <ll> b;
string s,ans;

void init(){
    best = 0;
    pos = -1;
    ans = "";
}

void manacher(){
    ll sz = s.size();
    ll l = 1, r = 1;
    b[0] = 1;
    b[sz-1] = 1;
    for (ll i = 1; i<sz-1; i++){
        b[i] = max(0LL, min(r-i, b[l + (r-i)]));
        while(s[i - b[i]] == s[i + b[i]]) b[i]++;
        
        if (i + b[i] > r){
            l = i - b[i], r = i + b[i];
        }
    }
}


int main(){
    fast;
    init();
    string t;
    cin>>t;
    n = t.size();
    s = "#";
    for (int i = 0; i<n; i++){
        s += t[i];
        s += "#";
    }
    b.resize(s.size());
    manacher();
    
    //for (auto au : b) cout<<au<<" ";
    //cout<<nl; 

    //Even positions denote odd palindromes.
    //Odd positions denote even palindromes.
    for (int i = 0; i<b.size(); i++){
        if (i%2 == 0){ //this is a '#' (counting even length palindromes).
            ll amou = (b[i]-1)/2;
            ll len = amou*2;
            if (best < len){
                best = len;
                pos = i;
            }
        }
        else{ //this is an actual character (counting odd length palindromes).
            ll amou = b[i]/2;
            ll len = (amou*2)-1;
            if (best < len){
                best = len;
                pos = i;
            }
        }
    }
    
    if (pos%2 == 1){ //even palindrome as the longest one.
        target = (b[pos]/2)-1;
        ans = s[pos];
    }
    else{ //odd palindrome as the longest one.
        target = (b[pos]-1)/2;
    }

    ind = pos+1;
    cont = 0;
    string aux = "";
    while(cont < target && ind < s.size()){
        if (s[ind] != '#') aux += s[ind], cont++;
        ind++;
    }
    ans += aux;
    reverse(aux.begin(),aux.end());
    string ress = aux;
    ress += ans;
    for (int i = 0; i<ress.size(); i++){
        if (ress[i] != ' ') cout<<ress[i];
    }
    cout<<nl;
    return 0;
}