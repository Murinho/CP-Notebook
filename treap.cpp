//Tested with: https://www.spoj.com/problems/ADACROP/
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
#define PI 3.1415926535
#define lsb(x) ((x)&(-x))
    
using namespace std;

typedef struct item *pitem;

struct item {
	int pr,key,cnt;
	pitem l,r;
	item(int key):key(key),pr(rand()),cnt(1),l(0),r(0) {}
    item(int key, int pr): key(key), pr(pr), cnt(1), l(0), r(0) {}
};
int cnt(pitem t){return t?t->cnt:0;}
void upd_cnt(pitem t){if(t)t->cnt=cnt(t->l)+cnt(t->r)+1;}
void split(pitem t, int key, pitem& l, pitem& r){ // l: < key, r: >= key
	if(!t)l=r=0;
	else if(key<t->key)split(t->l,key,l,t->l),r=t;
	else split(t->r,key,t->r,r),l=t;
	upd_cnt(t);
}
void insert(pitem& t, pitem it){
	if(!t)t=it;
	else if(it->pr > t->pr)split(t,it->key,it->l,it->r),t=it;
	else insert(it->key<t->key?t->l:t->r,it);
	upd_cnt(t);
}
void merge(pitem& t, pitem l, pitem r){
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),t=l;
	else merge(r->l,l,r->l),t=r;
	upd_cnt(t);
}
void erase(pitem& t, int key){
	if(t->key==key)merge(t,t->l,t->r);
	else erase(key<t->key?t->l:t->r,key);
	upd_cnt(t);
}
void unite(pitem &t, pitem l, pitem r){
	if(!l||!r){t=l?l:r;return;}
	if(l->pr<r->pr)swap(l,r);
	pitem p1,p2;split(r,l->key,p1,p2);
	unite(l->l,l->l,p1);unite(l->r,l->r,p2);
	t=l;upd_cnt(t);
}

map <int,pitem> mp;

int check(pitem t, int val){ //Explore the treap going left or right according to the target value.
    if (!t) return 0;
    int ans = 0;
    if (t->key >= val){
        ans += check(t->l,val);
    }
    else{ //if t->key < val
        ans += cnt(t->l)+1;
        ans += check(t->r,val);
    }
    return ans;
}

int main(){
    fast;
    srand(time(0));
    ll n,q;
    cin>>n>>q;
    vector <ll> a(n);
    fore(i,0,n){ //Having individual treaps for each number, the keys are the positions in the array.
        cin>>a[i];
        insert(mp[a[i]],new item(i));
    }
    while(q--){
        int pos,nw;
        cin>>pos>>nw;
        erase(mp[a[pos]],pos);
        a[pos] = nw;
        insert(mp[a[pos]], new item(pos));
        cout<<check(mp[a[pos]],pos)<<nl;
    }
    return 0;
}