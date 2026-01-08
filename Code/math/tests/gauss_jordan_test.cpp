// Tested with AC: https://codeforces.com/gym/100923/problem/C
#include <bits/stdc++.h>
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
#define fst first
#define snd second
#define eb emplace_back
#define ppb pop_back
#define i128 __int128_t
#define ull unsigned long long
 
using namespace std;

static const double EPS = 1e-9;
static const int INF = 2;
static const int maxn = 205;

static inline int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

ll a[maxn][maxn];
double b[maxn][maxn];
vector < vector <double> > c;
vector <double> ans;
ll n;

void solve(){
	cin >> n;
	c.clear();
	c.resize(n+1);
	fore(i,0,n){
		c[i].resize(n+1,0.0);
		fore(j,0,n){
			cin >> a[i][j];
			c[i][j] = (double)a[i][j];
		}
	}
	c[n].resize(n+1,0.0);

	fore(i,0,n){
		c[i][n] = 1.0;
		gauss(c,ans); // there will be always a solution, says the problem.
		c[i][n] = 0.0;
		
		fore(j,0,n){
			b[j][i] = ans[j]; 
		}
	}
	
	// print the answer:
	fore(i,0,n){
		fore(j,0,n) cout << fixed << setprecision(9) << b[i][j] << " ";
		cout << nl;
	}
	
	return;
}

int main(){
    fast;
    freopen("bujor.in", "r", stdin);
    freopen("bujor.out", "w", stdout);
    ll tc;
    cin>>tc;
    while(tc--){
        solve();
    }
}