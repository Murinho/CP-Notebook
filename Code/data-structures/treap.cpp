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

//Explore the treap going left or right according to the target value.
ll explore(pitem t, ll key){
    if (!t) return 0;
    ll res = 0;
    if (t->key < key){
        res += cnt(t->l) + 1;
        res += explore(t->r,key);
    }
    else{ //t->key >= key
        res += explore(t->l,key);
    }
    return res;
}

void kthSmallest(pitem t, int sz, int &kth){
    if (!t) return;
    if (cnt(t->l) + 1 == sz){
        kth = t->key;
        return;
    }
    else if(cnt(t->l) + 1 < sz){
        kthSmallest(t->r,sz - cnt(t->l) - 1,kth);
    }
    else kthSmallest(t->l,sz,kth);
}

void kthLargest(pitem t, int sz, ll &kth){
    if (!t) return;
    if (cnt(t->r) + 1 == sz){
        kth = t->key;
        return;
    }
    else if (cnt(t->r) + 1 < sz){
        kthLargest(t->l,sz - cnt(t->r) - 1, kth);
    }
    else kthLargest(t->r,sz,kth);
}

void solveCrops(){ //Spoj prefix crops problem.
    map <ll,pitem> mp;
    ll n,q;
    cin>>n>>q;
    vector <ll> a(n);
    //Having individual treaps for each number. 
    //The values are the positions in the array.
    fore(i,0,n){ 
        cin>>a[i];
        insert(mp[a[i]],new item(i));
    }
    while(q--){
        int pos,nw;
        cin>>pos>>nw;
        erase(mp[a[pos]],pos);
        a[pos] = nw;
        insert(mp[a[pos]], new item(pos));
        //check amount of items equal to a[pos] in [0,pos)
        cout<<explore(mp[a[pos]],pos)<<nl; 
    }
}

void solveDogs(){ //Codeforces Dogs Show problem.
    map <ll,pitem> mp;
    ll n,k,pos=0,best=0;
    cin>>n>>k;
    vector <ll> uni,a(n+1);
    fore(i,1,n+1){
        cin>>a[i];
        ll dif = max(0LL,a[i]-i);
        uni.pb(dif);
    }
    sort(ALL(uni));
    uni.erase(unique(ALL(uni)),uni.end());

    fore(i,1,n+1){
        insert(mp[max(0LL,a[i]-i)],new item(i));
    }
    fore(i,0,uni.size()){
        ll delay = uni[i];
        best = max(best,explore(mp[delay],k-delay));
        //join 2 treaps: {root,left,right};
        if (i+1<uni.size()) unite(mp[uni[i+1]],mp[uni[i+1]],mp[delay]); 
    }
    cout<<best<<nl;
}

int main(){ srand(time(0)); }