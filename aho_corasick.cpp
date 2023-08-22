#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define nl '\n'
#define rep(i,a,b) for(int i=(a);i<(b);i++)

using namespace std;

const int MAXN = 1e5 + 42;
 
map<char, int> to[MAXN];
int link[MAXN], que[MAXN], sz = 1, endlink[MAXN]; vector<int> leaf[MAXN];  vector<int> ans[MAXN];
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
        for(auto [c,u] : to[v])
        {
            int j = link[v];
            while(j && !to[j].count(c)) j=link[j];
            if(to[j].count(c) && to[j][c]!=u) link[u] = to[j][c];
            endlink[u] = leaf[link[u]].size()>0?link[u]:endlink[link[u]];
            q.push(u);
        }
    }
}
void walk(string s) { // Dado un conjunto de patrones encuentra todas las coincidencias en una string. aka KMP con muchos patrones.
    int v=0;
    rep(i,0,s.size()) {
        char c=s[i];
        while(v && !to[v].count(c)) v=link[v];
        if(to[v].count(c)) v=to[v][c]; 
        for(int u=v;u;u=endlink[u]) for(int x: leaf[u])
            ans[x].push_back(i);
    }
}

string s;
int n;
vector <string> a;
vector <int> b;
const int inf = 1e9;

void init(){
    a.resize(MAXN);
    b.resize(MAXN);
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin>>s;
    cin>>n;
    init();
    for (int i = 0; i<n; i++){
        cin>>b[i]>>a[i];
        add_str(a[i],i);
    }
    push_links();
    walk(s);
    for (int i = 0; i<n; i++){
        int res = inf;
        int sz = a[i].size();
        for (int j = b[i]-1; j<ans[i].size(); j++){
            int l = ans[i][j-b[i]+1];
            int r = ans[i][j] + sz;
            res = min(res,r-l);
        }
        if (res == inf) cout<<-1<<nl;
        else cout<<res<<nl;
    }
    return 0;
}