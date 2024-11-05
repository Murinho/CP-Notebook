// Tested with: https://cses.fi/problemset/task/1706/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a; i<b; i++)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector <vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second

using namespace std;

const ll maxn = 1e5+50;
const ll maxnsq = 400;

ll vis[maxn],amou=0,n,m,cnt[maxn],dp[maxnsq][maxn];
vi c,adj[maxn];

void dfs(int node){
    vis[node]=1;
    amou++;
    for(auto au : adj[node]) if (!vis[au]) dfs(au);
}

/*  0/1 Knapsack optimization where sum of all items is ~ N
    There will be at most sqrt(N) different items.
    Array 'cnt' represents the count of a specific item.
*/
void calculateDp(){ //DP in O(N*sqrt(N))
    dp[0][0]=0;
    fore(i,1,n+5) dp[0][i] = -1;
    fore(i,1,sz(c)){
        fore(j,1,n+1){
            if(dp[i-1][j] >= 0)
                dp[i][j] = 0;
            else if(j-c[i] >= 0 && dp[i][j - c[i]] >= 0 and dp[i][j - c[i]] < cnt[c[i]])
                dp[i][j] = dp[i][j - c[i]] + 1;
            else
                dp[i][j] = -1;
        }
    }
}

int main(){
    fast;
    cin>>n>>m;
    fore(i,0,m){
        ll x,y;
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    fore(i,1,n+1) if (!vis[i]){
        amou=0;
        dfs(i);
        cnt[amou]++;
        c.pb(amou);
    }
    c.pb(0);
    sort(ALL(c));
    c.erase(unique(ALL(c)),c.end());
    calculateDp();

    ll tam = sz(c);
    fore(i,1,n+1){
        if (dp[tam-1][i]>=0) cout<<1;
        else cout<<0;
    }
    cout<<nl;
    return 0;
}