// Tested with: https://www.spoj.com/problems/DQUERY/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define rofe(i,a,b) for(ll i=a-1;i>=b;--i)
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

const int maxn = 1e6+5;

struct qu{int l,r,id;};

ll n,nq,sq,res;

bool qcomp(const qu &a, const qu &b){
    if(a.l/sq!=b.l/sq) return a.l<b.l;
    return (a.l/sq)&1?a.r<b.r:a.r>b.r;
}
qu qs[maxn];
ll a[maxn],cnt[maxn],ans[maxn];

void add(int i){
    if (cnt[a[i]] == 0) res++;
    cnt[a[i]]++;
}

void remove(int i){
    cnt[a[i]]--;
    if (cnt[a[i]] == 0) res--;
}

ll get_ans(){
    return res;
}

void mos(){
    fore(i,0,nq) qs[i].id=i;
    sq = sqrt(n)+0.5;
    sort(qs,qs+nq,qcomp);
    int l=0,r=0;
    res=0;
    fore(i,0,nq){ // Must have queries like: [l,r)
        qu q=qs[i];
        while(l>q.l)add(--l);
        while(r<q.r)add(r++);
        while(l<q.l)remove(l++);
        while(r>q.r)remove(--r);
        ans[q.id]=get_ans();
    }
}

int main(){
    fast;     
    cin>>n;
    fore(i,0,n) cin>>a[i];
    cin>>nq;
    fore(i,0,nq) cin>>qs[i].l>>qs[i].r, qs[i].l--;
    mos();
    fore(i,0,nq) cout<<ans[i]<<nl;
    return 0;
}