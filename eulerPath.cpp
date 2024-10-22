// Tested with: https://cses.fi/problemset/task/1691
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

const int maxn = 1e5+5;
int m, n;
vector<int> res;
set <int> adj[maxn];

void dfs(int curr)
{
    auto &edges = adj[curr]; 
    while(!edges.empty())
    {
        auto edge = *edges.begin();
        edges.erase(edge);
        adj[edge].erase(curr);
        dfs(edge);
    }
    res.push_back(curr);
}

//Going from node 1, passing through all edges without repeating and come back to node 1.
int main(){
    cin >> n >> m;
    fore(i,0,m){
        int x, y;
        cin >> x >> y;
        adj[x].insert(y);
        adj[y].insert(x);  
    }
    
    fore(i,1,n+1){
        if (sz(adj[i])%2){
            cout<<"IMPOSSIBLE"<<nl;
            return 0;
        }
    }

    dfs(1);
    
    if (sz(res) != m + 1){
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    
    for(auto au : res) cout<<au<<" ";
    cout<<nl;
    return 0;
}