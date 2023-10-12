#include <bits/stdc++.h>
#define ll long long
#define nl '\n'
#define pb push_back
#define ld long double
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define fast                                                                   \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define PI 3.1415926535
 
using namespace std;
 
const ll mod = 1e9+7;
 
const int MAXN = 1e6+10;
 
map<char, int> to[MAXN];
vector <string> a; 
int lnk[MAXN];
ll que[MAXN];
ll sz = 1;
ll endlink[MAXN]; 
vector<int> leaf[MAXN];  
vector <int> ans[MAXN];
void add_str(string s, int id) {
    int v = 0;
    for(char c: s) {
        if(!to[v].count(c)) to[v][c] = sz++;
        v = to[v][c];
    }
    leaf[v].push_back(id);
}
void push_links() {
    queue<int> q({0});
    while(!q.empty()) {
        int v = q.front(); q.pop();
        for(auto [c,u]: to[v])
        {
            int j = lnk[v];
            while(j && !to[j].count(c)) j=lnk[j];
            if(to[j].count(c) && to[j][c]!=u) lnk[u] = to[j][c];
            endlink[u] = leaf[lnk[u]].size()>0?lnk[u]:endlink[lnk[u]];
            q.push(u);
        }
    }
}
void walk(string s) { // Dado un conjunto de patrones encuentra todas las coincidencias en una string. aka KMP con muchos patrones.
    int v=0;
    rep(i,0,s.size()) {
        char c=s[i];
        while(v && !to[v].count(c)) v=lnk[v];
        if(to[v].count(c)) v=to[v][c]; 
        for(int u=v;u;u=endlink[u]) for(int x: leaf[u]){
            //x: indice de la palabra:
            //i: donde termina
            ll tami = a[x].size();
            ans[x].pb(i); //esta es mi respuesta, pusheo el indice donde termina
        }  
    }
}
 
 
 
void init(int n){
    a.resize(n+1);
}
 
int main() {
    fast;
    string s;
    int n;
    cin>>s;
    s = "$" + s;
    ll len = s.size();
    cin>>n;
    init(n);
    for (int i = 1; i<=n; i++){
        cin>>a[i];
        add_str(a[i],i);
    }
    push_links();
    walk(s);
    for (int i = 1; i<=n; i++){
        cout<<a[i]<<" termina en: ";
        for (auto au : ans[i]) cout<<au<<" ";
        cout<<nl;
    }
    return 0;
}
