//Tested with https://cses.fi/problemset/task/2102/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define vi vector <ll>
#define vvi vector<vi>
#define PI 3.1415926535
    
    
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

bool check(string t){
    int pos = 0;
    int tam = t.size();
    int node = 0;
    while(pos < tam){
        if (st[node].next[t[pos]] == 0) return false; //if a node doesn't have a link to the next letter, then impossible.
        node = st[node].next[t[pos]];
        pos++;
    }
    return true; //all characters exist.
}

int main(){
    fast;
    cin>>s;
    int n = s.size();
    sa_init(); //initialize, don't forget !!!
    fore(i,0,n) sa_extend(s[i]); //insertion of the big text char by char.
    ll q;
    cin>>q;
    while(q--){ //check if a pattern is contained in the big text.
        string t;
        cin>>t;
        if (check(t)) cout<<"YES"<<nl;
        else cout<<"NO"<<nl;
    }
    return 0;
}