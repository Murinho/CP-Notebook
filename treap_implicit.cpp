//Tested with: https://www.spoj.com/problems/TAP2014K/
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
	int pr,cnt;
	int val;
	bool rev;int add;
	pitem l,r;
	item(int val): pr(rand()),cnt(1),val(val),l(0),r(0),rev(0),add(0) {}
};
void push(pitem it){
	if(it){
		if(it->rev){
			swap(it->l,it->r);
			if(it->l)it->l->rev^=true;
			if(it->r)it->r->rev^=true;
			it->rev=false;
		}
        //remove %26 when values can get bigger.
		it->val=(it->val+it->add)%26; 
		if(it->l)it->l->add+=it->add;
		if(it->r)it->r->add+=it->add;
		it->add=0;
	}
}
int cnt(pitem it){return it?it->cnt:0;}
void upd_cnt(pitem it){
	if(it){
		it->cnt=cnt(it->l)+cnt(it->r)+1;
	}
}
void merge(pitem& t, pitem l, pitem r){
	push(l);push(r);
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),t=l;
	else merge(r->l,l,r->l),t=r;
	upd_cnt(t);
}
void split(pitem t, pitem& l, pitem& r, int sz){ // sz:desired size of l
	if(!t){l=r=0;return;}
	push(t);
	if(sz<=cnt(t->l))split(t->l,l,t->l,sz),r=t;
	else split(t->r,t->r,r,sz-1-cnt(t->l)),l=t;
	upd_cnt(t);
}

void imprimir(pitem t){
    if (!t) return;
    push(t);
    imprimir(t->l);
    cout<<(char)('a' + t->val);
    imprimir(t->r);
}

int main(){
    fast;
    srand(time(0));
    ll tc,n,q;
    string s;
    cin>>tc;
    while(tc--){
        cin>>s>>q;
        n = s.size();
        pitem t = 0; //raiz de todos.
        fore(i,0,n) merge(t,t,new item(s[i]-'a'));
        /*Cada query:
        1. [ini,fin], [ini2,fin2] swappearlos.
        2. [ini,fin], [ini2,fin2] revertirlos individualmente.
        3. [ini,fin], [ini2,fin2] agregar +1 todo el segmento.
        */
        while(q--){
            int ini,fin,ini2,fin2;
            cin>>ini>>fin>>ini2>>fin2;
            ini--; ini2--;
            pitem t1,t2,t3,t4;
            split(t,t,t4,fin2); //{root, assign left, assign right, size of left subarray}.
            split(t,t,t3,ini2);
            split(t,t,t2,fin);
            split(t,t,t1,ini);
            t1->rev ^= true; t1->add++; //reversing and add+1.
            t3->rev ^= true; t3->add++;
            merge(t,t,t3);
            merge(t,t,t2);
            merge(t,t,t1);
            merge(t,t,t4);
        }
        imprimir(t);
        cout<<nl;
    }
    return 0;
}