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

void mos(){ // example amount of distinct elements in [l,r)
    fore(i,0,nq) qs[i].id=i;
    sq = sqrt(n)+0.5;
    sort(qs,qs+nq,qcomp); //sort the queries.
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