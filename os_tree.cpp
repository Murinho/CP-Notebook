//Tested with: https://cses.fi/problemset/task/1076
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((int)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
 
using namespace __gnu_pbds;
using namespace std;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int,null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;

const ll maxn = 2e5+100;
ll n,a[maxn],k;

//find_by_order(k): finds the element that is the Kth in the set.
//order_of_key(k): finds the number of elements strictly smaller than k. 

int main(){
    fast;
    cin>>n>>k;
    ordered_multiset omst;
    fore(i,1,n+1) cin>>a[i];

    queue < pair <int,int> > q;

    fore(i,1,n+1){
        if (q.size() == k){
            if (k%2) cout<<(*omst.find_by_order(k/2)).first<<" ";
            else cout<<(*omst.find_by_order(k/2 - 1)).first<<" ";

            int f = q.front().first;
            q.pop();
            omst.erase(omst.find_by_order(omst.order_of_key({f,-1})));
        }
        omst.insert({a[i],i});
        q.push({a[i],i});
    }
    if (k%2) cout<<(*omst.find_by_order(k/2)).first<<nl;
    else cout<<(*omst.find_by_order(k/2 - 1)).first<<nl;
    return 0;
}