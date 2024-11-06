const ll maxn = 1e6 + 5;
const ll mod = 1e9+7;
ll f[maxn];

ll expo(ll x, ll pw){ 
    ll res = 1;
    while(pw > 0){
        if(pw&1)
            res = (res*x)%mod;
        x = (x*x)%mod;
        pw >>= 1;
    }
    return res;
}

ll nCk(ll a, ll b){ //precalculate factorials % mod.
    b = (f[b]*f[a-b])%mod;
    ll inverse = expo(b,mod-2); 
    ll res = (f[a]*inverse)%mod;
    return res;
}
