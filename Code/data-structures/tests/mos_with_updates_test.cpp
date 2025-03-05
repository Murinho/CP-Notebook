#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define lsbpos(x) __builtin_ffs(x)
#define PI acos(-1.0)
#define pii pair<ll,ll>
#define fst first
#define snd second
#pragma GCC target("popcnt")
 
using namespace std;

const ll maxn = 2e5+5;

struct qu{ll l,r,t,id;};

struct upd{ll pos,val;};

ll n,nq,sq,nu,res,len;

qu qs[maxn];
upd ups[maxn];
ll a[maxn],cnt[maxn],ans[maxn];
ll belong[maxn],lef[maxn],rig[maxn];

bool qcomp(const qu &x, const qu &y){
    if (belong[x.l] != belong[y.l]) return x.l < y.l;
    if (belong[x.r] != belong[y.r]) return x.r < y.r;
    return x.t < y.t;
}

void prepare(){
	len = pow(n,0.66666);
	sq = ceil(1.0*n/len);
	fore(i,0,sq){
		rig[i]=i*len;
		lef[i+1] = rig[i]+1;
	}
	rig[sq]=n-1;
	fore(i,1,sq+1){
		fore(j,lef[i],rig[i]+1) belong[j]=i;
	}
}

void add(ll i){
    if (cnt[a[i]] == 0) res++;
    else if (cnt[a[i]] == 1) res--;
    cnt[a[i]]++;
}

void remove(ll i){
    if (cnt[a[i]] == 1) res--;
    else if (cnt[a[i]] == 2) res++;
    cnt[a[i]]--;
}

void update(ll id, ll l, ll r){
	ll pos = ups[id].pos;
	if (l <= pos && pos < r) remove(pos);
	swap(a[pos],ups[id].val);
	if (l <= pos && pos < r) add(pos);
}

ll get_ans(){
    return res;
}

void mos(){ // example amount of distinct elements in [l,r)
    fore(i,0,nq) qs[i].id=i;
    prepare();
    sort(qs,qs+nq,qcomp); //sort the queries.
    ll l=0,r=0;
    ll ut=0; //update time.
    res=0;
    fore(i,0,nq){ // Must have queries like: [l,r)
        qu q=qs[i];
        // move query range.
        while(l>q.l)add(--l);
        while(r<q.r)add(r++);
        while(l<q.l)remove(l++);
        while(r>q.r)remove(--r);
        
        // do and undo updates
        while (ut < q.t) update(ut,l,r), ut++;
        while(ut > q.t) ut--, update(ut,l,r);
        //get answer.
        ans[q.id]=get_ans();
    }
}

int main(){
    fast;
    ll ops;
	cin>>n>>ops;
	fore(i,0,n) cin>>a[i];
	
	nq = nu = 0;
	fore(i,0,ops){
		ll x,y,z;
		cin>>x>>y>>z;
		if (x == 1){ //update.
			ups[nu].pos = y;
			ups[nu].val = z;
			nu++;
		}
		else{ //query.
			z++;
			qs[nq].l = y;
			qs[nq].r = z;
			qs[nq].t = nu;
			nq++;
		}
	}
	
	if (nq>0){
		mos();
		fore(i,0,nq) cout<<ans[i]<<nl;
	}
	return 0;
}