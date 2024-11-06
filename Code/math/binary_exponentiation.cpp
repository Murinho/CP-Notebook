const ll mod = 1e9+7;

ll expo(ll x, ll pw){ 
    ll res = 1;
    while(pw > 0){
        if(pw&1)
            res = (res*x)%mod;
        x = (x*x)%mod;
        pw >>= 1;
    }
    return res;
} // For mul-inverses: pw = mod-2