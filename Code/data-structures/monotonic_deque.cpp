//Tested with: https://www.hackerrank.com/challenges/queries-with-fixed-length/problem
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((int)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second
 
using namespace std;

const ll maxn = 2e5+10;

ll n,qys,a[maxn];
deque <int> q; //monotonic deque keeping maximums in front.

void add(int x){ 
    while(!q.empty() && q.back() < x) q.pop_back();
    q.pb(x);
}

void remove(int x){
    if (!q.empty() && q.front() == x) q.pop_front();
}

void clear(){
    while(!q.empty()) q.pop_back();
}

int getBest(){ return q.front(); }

void solve(){
    while(qys--){
        int l=1,r,ans;
        clear();
        cin>>r;
        fore(i,1,r+1) add(a[i]);
        ans = getBest();
        while(r<n){
            remove(a[l]);
            l++, r++;
            add(a[r]);
            ans = min(ans,getBest());
        }
        cout<<ans<<nl;
    }
}

int main(){
    fast;
    cin>>n>>qys;
    fore(i,1,n+1) cin>>a[i];
    solve();
}
