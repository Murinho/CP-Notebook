// Tested with AC: https://cses.fi/problemset/task/3154/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define rofe(i,a,b) for(ll i=a-1;i>=b;--i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define lsbpos(x) __builtin_ffs(x)
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define f first
#define s second
#define eb emplace_back
#define ppb pop_back
#define i128 __int128_t
#define ull unsigned long long
 
using namespace std;

static const ll MOD = 1e9+7;

static inline ll modpow(ll a, ll e){
    ll r = 1;
    while(e > 0){
        if (e & 1) r = (r * a ) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}
/*
Solves A x = b (mod MOD).
Input matrix 'a' is n x (m+1) augmented: a[i][0..m-1] are coefficients, a[i][m] is RHS.
Returns:
  0 -> no solution
  1 -> unique solution (ans filled)
  2 -> infinitely many solutions (ans is one solution with free vars = 0)
*/
static inline int gauss_mod(vector<vector<ll>> a, vector<ll> &ans){
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;

    vector<int> where(m, -1);

    for(int col = 0, row = 0; col < m && row < n; ++col){
        int sel = -1;
        for(int i = row; i < n; ++i){
            if (a[i][col] != 0){
                sel = i;
                break;
            }
        }
        if (sel == -1) continue;

        swap(a[sel], a[row]);
        where[col] = row;

        // Scale pivot row so pivot becomes 1
        ll inv_pivot = modpow(a[row][col], MOD-2);
        for(int j = col; j <= m; ++j){
            a[row][j] = (a[row][j] * inv_pivot ) % MOD;
        }

        // Eliminate this column from all other rows
        for(int i = 0; i < n; ++i){
            if (i == row) continue;
            if (a[i][col] == 0) continue;

            ll factor = a[i][col]; // since pivot is 1
            for(int j = col; j <= m; ++j){
                a[i][j] = (a[i][j] - (ll)(factor * a[row][j] % MOD));
                a[i][j] += MOD;
                a[i][j] %= MOD;
            }
        }

        ++row;
    }

    // Build one solution (free vars = 0)
    ans.assign(m, 0);
    for(int i = 0; i < m; ++i){
        if (where[i] != -1){
            ans[i] = a[where[i]][m]; // pivot is 1
        }
    }

    // Check consistency: 0...0 | c (c != 0) => no solution
    for(int i = 0; i < n; ++i){
        bool all0 = true;
        for(int j = 0; j < m; ++j){
            if (a[i][j] != 0){
                all0 = false;
                break;
            }
        }
        if (all0 && a[i][m] != 0) return 0;
    }

    // If any variable is free -> infinite solutions
    for(int i = 0; i < m; ++i){
        if (where[i] == -1) return 2;
    }
    return 1;
}

int main(){
    fast;
    int n,m;
    cin >> n >> m;
    vvi g(n,vi(m+1));
    
    fore(i,0,n){
    	fore(j,0,m+1) cin >> g[i][j];
    }
    
    vi ans;
    int ret = gauss_mod(g,ans);
    if (ret == 0) cout << -1 << nl;
    else{
    	for(auto &elm : ans) cout << elm << " ";
    	cout << nl;
    }
    return 0;
}