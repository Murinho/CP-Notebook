//Tested with: https://cses.fi/problemset/task/2105/
//Tested with: https://cses.fi/problemset/task/2108
#include <bits/stdc++.h>
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

using namespace std;

const ll maxn = 1e6+5;
struct state {int len,link;map<char,int> next;}; //clear next!!
state st[maxn];
int sz,last;
string s;

void sa_init(){
	last=st[0].len=0;sz=1;
	st[0].link=-1;
}
void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}


//Finds longest common substring in 2 substrings.
string lcs (string S, string T) { 
    sa_init();
    for (int i = 0; i < S.size(); i++)
        sa_extend(S[i]);

    int v = 0, l = 0, best = 0, bestpos = 0;
    for (int i = 0; i < T.size(); i++) {
        while (v && !st[v].next.count(T[i])) {
            v = st[v].link ;
            l = st[v].len;
        }
        if (st[v].next.count(T[i])) {
            v = st [v].next[T[i]];
            l++;
        }
        if (l > best) {
            best = l;
            bestpos = i;
        }
    }
    return T.substr(bestpos - best + 1, best);
} 
  
ll f(ll x, vector <ll> &dp){
    if (dp[x] >= 0) return dp[x];
    ll res = 1;
    for(map <char,int>::iterator it=st[x].next.begin(); it!=st[x].next.end(); it++) res += f(it->second,dp);
    dp[x] = res;
    return dp[x];
}

//Finds the total length of different substrings.
ll get_tot_len_diff_substings(){
    ll tot = 0;
    for(int i = 1; i < sz; i++) {
        ll shortest = st[st[i].link].len + 1;
        ll longest = st[i].len;

        ll num_strings = longest - shortest + 1;
        ll cur = num_strings * (longest + shortest) / 2;
        tot += cur;
    }
    return tot;
}

//Finds the amount of distinct substrings.
void distinctSubstrings(){
    cin>>s;
    int n = s.size();
    vector <ll> dp(maxn+5,-1);
    sa_init();
    fore(i,0,n) sa_extend(s[i]);
    ll ans = f(0,dp)-1;
    cout<<ans<<nl;
}

void dfs(int node, ll k, vector<ll> &dp, vector <char> &path){
    if (k < 0) return;
    for(const auto &[c,signode]: st[node].next){
        if (dp[signode] <= k) k -= dp[signode];
        else{
            path.pb(c);
            dfs(signode,k-1,dp,path);
            return;
        }   
    }
}

//Finds the Kth biggest substring.
void substringOrder(){
    string s;
    ll k;
    cin>>s;
    cin>>k;
    int n = s.size();
    vector <ll> dp(maxn+5,-1);
    sa_init();
    fore(i,0,n) sa_extend(s[i]);
    f(0,dp);
    vector <char> path;
    dfs(0,k-1,dp,path);
    for(auto c : path) cout<<c;
    cout<<nl;
}   

int main(){
    fast;
    //distinctSubstrings();
    //substringOrder();
}