#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fast cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
#define nl '\n'

using namespace std;

ll tc,n,m,k,ans,best,x,y,spnode,cynum;
vector < vector <ll> > cycles;
vector < set <ll> > stadj;
vector < set <ll> > stcy;
vector <ll> color,par;
vector <ll> extra;
bool flag;

void init(){
    cycles.clear(), cycles.resize(0);
    stcy.clear(), stcy.resize(0);
    color.clear(), color.resize(n+1);
    par.clear(), par.resize(n+1);
    stadj.clear(), stadj.resize(n+1);
    flag = false;
}

void dfs_cycle(int u, int p)
{
    if (color[u] == 2) {
        return;
    }
    if (color[u] == 1) {
        vector<ll> v;
        set <ll> st;
           
        int cur = p;
        v.push_back(cur);
        st.insert(cur);
 
        while (cur != u) {
            cur = par[cur];
            v.push_back(cur);
            st.insert(cur);
        }
        cycles.pb(v);
        stcy.pb(st);
        return;
    }
    par[u] = p;
 
    color[u] = 1;
 
    for (int v : stadj[u]) {
        if (v == par[u]) {
            continue;
        }
        dfs_cycle(v, u);
    }
    color[u] = 2;
}
 

int main(){
    fast;
    cin>>tc;
    while(tc--){
        cin>>n>>m;
        init();
        for (int i = 1; i<=m; i++){
            cin>>x>>y;
            stadj[x].insert(y);
            stadj[y].insert(x);
        }
        for (int i = 1; i<=n; i++) if (color[i] == 0) dfs_cycle(i,0);

        //Print the cycles of the graph:
        int cypos = -1;
        for (auto cy : cycles){
            if (flag) break;
            cypos++;
            for (auto node : cy){
                extra.clear(), extra.resize(0);
                for (auto signode : stadj[node]){
                    if (!stcy[cypos].count(signode)){
                        extra.pb(signode);
                    }
                    if (extra.size() >= 2) break;
                }
                if (extra.size() >= 2){
                    flag = true;
                    cynum = cypos;
                    spnode = node;
                    break;
                }
            }
        }
        if(!flag) cout<<"NO"<<nl;
        else{
            cout<<"YES"<<nl;
            cout<<cycles[cynum].size() + 2 <<nl;
            cycles[cynum].pb(cycles[cynum][0]);
            for (int i = 1; i<cycles[cynum].size(); i++){
                cout<<cycles[cynum][i-1]<<" "<<cycles[cynum][i]<<nl;
            }
            cout<<spnode<<" "<<extra[0]<<nl;
            cout<<spnode<<" "<<extra[1]<<nl;
        }
    }
    return 0;
}