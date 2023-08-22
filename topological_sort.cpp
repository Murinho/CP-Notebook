#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

int n,m,a,b,edges = 0;
map <int, vector <int> > mp;
map <int, int> indegree;
queue <int> q;
vector <int> topo;

int main()
{
    cin>>n>>m; ///Amount of nodes and edges in the DAG.
    for (int i = 0; i<m; i++){
        cin>>a>>b; ///a --> b.
        mp[a].pb(b);
        indegree[b]++;
    }
    for (int i = 0; i<n; i++){
        if (indegree[i] == 0){
            q.push(i);
        }
    }
    while (!q.empty()){
        int node = q.front();
        q.pop();
        topo.pb(node);
        for (int i = 0; i<mp[node].size(); i++){
            int signode = mp[node][i];
            indegree[signode]--;
            if (indegree[signode] == 0){
                q.push(signode);
            }
        }
    }
    if (topo.size() != n){
        cout<<"There is a cycle in the DAG, impossible then. "<<endl;
        return 0;
    }
    for (int i = 0; i<n; i++){
        cout<<topo[i]<<" ";
    }
    return 0;
}
