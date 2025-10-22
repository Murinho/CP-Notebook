const ll maxn = 1e6 + 5;
const ll M = 1e9+9; // prime modulo (alternative: 10000000000000061 or 10000000000061)
const ll B = 131; // prime number bigger than the alphabet.
string s,t;
ll pws[maxn],h[maxn],tams,tamt,hasht=0,ans=0;

ll conv(char c){
    return (c-'a'+1);
}

bool sameHash(int l1, int len1, int l2, int len2){
    int r1 = l1 + len1;
    int r2 = l2 + len2;
    ll h1 = (h[r1]-h[l1]*pws[len1]%M + M)%M;
    ll h2 = (h[r2]-h[l2]*pws[len2]%M + M)%M;
    return h1 == h2;
}

void precalc(){
    tams = sz(s), tamt = sz(t);
    pws[0] = 1;
    fore(i,1,maxn) pws[i] = (pws[i-1]*B)%M; 

    // Main hash.
    h[0] = conv(s[0]);
    fore(i,0,tams) h[i+1] = ((h[i]*B)+conv(s[i]))%M;

    // Target hash.
    fore(i,0,tamt) hasht = ((hasht*B)+conv(t[i]))%M;
}

void doit(){
    cin>>s; //main text.
    cin>>t; //pattern.
    precalc();

    //For all substrings, check if hashings of substring 's' and 't' are equal:
    fore(i,tamt,tams+1){
        ll cur_hash = (h[i]-h[i-tamt]*pws[tamt]%M + M)%M;
        if (cur_hash == hasht) ans++;
    }
}