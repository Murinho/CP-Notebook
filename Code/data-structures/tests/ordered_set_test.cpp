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
#define fst first
#define snd second
#define pii pair <ll,ll>
 
using namespace __gnu_pbds;
using namespace std;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int,null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;

const ll maxn = 2e5+100;
ll n,a[maxn],k;
ordered_multiset omst;

//find_by_order(k): finds the element that is the Kth in the set.
//order_of_key(k): finds the number of elements strictly smaller than k (or {k,pos} if multiset).

ll get_kth_element(ll k){ return (*omst.find_by_order(k)).fst;} // 0-indexed.

ll get_elements_less_than_k(ll k, ll pos){ return (omst.order_of_key({k, pos}));}

void insert(ll val, ll pos){ omst.insert({val,pos}); }

void erase(ll val, ll pos){ omst.erase(omst.find_by_order(omst.order_of_key({val,pos})));}

int main(){
    fast;
    cin>>n>>k;
    fore(i,1,n+1) cin>>a[i];
    queue < pii > q;
    fore(i,1,n+1){
        if (sz(q) == k){
            if (k%2) cout<<get_kth_element(k/2)<<" ";
            else cout<<get_kth_element(k/2 - 1)<<" ";

            int f = q.front().first;
            int s = q.front().second;
            q.pop();
            erase(f,s);
        }
        insert(a[i],i);
        q.push({a[i],i});
    }
    if (k%2) cout<<get_kth_element(k/2)<<nl;
    else cout<<get_kth_element(k/2 - 1)<<nl;
    return 0;
}