//AC --> Tested with: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
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

const ll maxn = 2e5+5;
const ll lzneut = 0;
const ll neut = 0;
const ll INF = 1e18+5;
const ll mod = 1e9+7;

struct Node{
    ll sum,max1,max2,maxc,min1,min2,minc,lazy;
};

ll a[maxn],N;

struct STBeats{
    vector <Node> st; int n;
    STBeats(int n): st(4*n + 5), n(n) {}

    void merge(int t) {
        // sum
        st[t].sum = st[t << 1].sum + st[t << 1 | 1].sum;

        // max
        if (st[t << 1].max1 == st[t << 1 | 1].max1) {
            st[t].max1 = st[t << 1].max1;
            st[t].max2 = max(st[t << 1].max2, st[t << 1 | 1].max2);
            st[t].maxc = st[t << 1].maxc + st[t << 1 | 1].maxc;
        } else {
            if (st[t << 1].max1 > st[t << 1 | 1].max1) {
                st[t].max1 = st[t << 1].max1;
                st[t].max2 = max(st[t << 1].max2, st[t << 1 | 1].max1);
                st[t].maxc = st[t << 1].maxc;
            } else {
                st[t].max1 = st[t << 1 | 1].max1;
                st[t].max2 = max(st[t << 1].max1, st[t << 1 | 1].max2);
                st[t].maxc = st[t << 1 | 1].maxc;
            }
        }

        // min
        if (st[t << 1].min1 == st[t << 1 | 1].min1) {
            st[t].min1 = st[t << 1].min1;
            st[t].min2 = min(st[t << 1].min2, st[t << 1 | 1].min2);
            st[t].minc = st[t << 1].minc + st[t << 1 | 1].minc;
        } else {
            if (st[t << 1].min1 < st[t << 1 | 1].min1) {
                st[t].min1 = st[t << 1].min1;
                st[t].min2 = min(st[t << 1].min2, st[t << 1 | 1].min1);
                st[t].minc = st[t << 1].minc;
            } else {
                st[t].min1 = st[t << 1 | 1].min1;
                st[t].min2 = min(st[t << 1].min1, st[t << 1 | 1].min2);
                st[t].minc = st[t << 1 | 1].minc;
            }
        }
    }

    void push_add(int t, int tl, int tr, ll v) {
        if (v == 0) { return; }
        st[t].sum += (tr - tl + 1) * v;
        st[t].max1 += v;
        if (st[t].max2 != -INF) { st[t].max2 += v; }
        st[t].min1 += v;
        if (st[t].min2 != INF) { st[t].min2 += v; }
        st[t].lazy += v;
    }

    // corresponds to a chmin update
    void push_max(int t, ll v, bool l) {
        if (v >= st[t].max1) { return; }
        st[t].sum -= st[t].max1 * st[t].maxc;
        st[t].max1 = v;
        st[t].sum += st[t].max1 * st[t].maxc;
        if (l) {
            st[t].min1 = st[t].max1;
        } else {
            if (v <= st[t].min1) {
                st[t].min1 = v;
            } else if (v < st[t].min2) {
                st[t].min2 = v;
            }
        }
    }

    // corresponds to a chmax update
    void push_min(int t, ll v, bool l) {
        if (v <= st[t].min1) { return; }
        st[t].sum -= st[t].min1 * st[t].minc;
        st[t].min1 = v;
        st[t].sum += st[t].min1 * st[t].minc;
        if (l) {
            st[t].max1 = st[t].min1;
        } else {
            if (v >= st[t].max1) {
                st[t].max1 = v;
            } else if (v > st[t].max2) {
                st[t].max2 = v;
            }
        }
    }

    void pushdown(int t, int tl, int tr) {
        if (tl == tr) return;
        // sum
        int tm = (tl + tr) >> 1;
        push_add(t << 1, tl, tm, st[t].lazy);
        push_add(t << 1 | 1, tm + 1, tr, st[t].lazy);
        st[t].lazy = 0;

        // max
        push_max(t << 1, st[t].max1, tl == tm);
        push_max(t << 1 | 1, st[t].max1, tm + 1 == tr);

        // min
        push_min(t << 1, st[t].min1, tl == tm);
        push_min(t << 1 | 1, st[t].min1, tm + 1 == tr);
    }

    void build(int t = 1, int tl = 0, int tr = N - 1) {
        st[t].lazy = 0;
        if (tl == tr) {
            st[t].sum = st[t].max1 = st[t].min1 = a[tl];
            st[t].maxc = st[t].minc = 1;
            st[t].max2 = -INF;
            st[t].min2 = INF;
            return;
        }

        int tm = (tl + tr) >> 1;
        build(t << 1, tl, tm);
        build(t << 1 | 1, tm + 1, tr);
        merge(t);
    }

    void update_add(int l, int r, ll v, int t = 1, int tl = 0, int tr = N - 1) {
        if (r < tl || tr < l) { return; }
        if (l <= tl && tr <= r) {
            push_add(t, tl, tr, v);
            return;
        }
        pushdown(t, tl, tr);

        int tm = (tl + tr) >> 1;
        update_add(l, r, v, t << 1, tl, tm);
        update_add(l, r, v, t << 1 | 1, tm + 1, tr);
        merge(t);
    }

    void update_chmin(int l, int r, ll v, int t = 1, int tl = 0, int tr = N - 1) {
        if (r < tl || tr < l || v >= st[t].max1) { return; }
        if (l <= tl && tr <= r && v > st[t].max2) {
            push_max(t, v, tl == tr);
            return;
        }
        pushdown(t, tl, tr);

        int tm = (tl + tr) >> 1;
        update_chmin(l, r, v, t << 1, tl, tm);
        update_chmin(l, r, v, t << 1 | 1, tm + 1, tr);
        merge(t);
    }

    void update_chmax(int l, int r, ll v, int t = 1, int tl = 0, int tr = N - 1) {
        if (r < tl || tr < l || v <= st[t].min1) { return; }
        if (l <= tl && tr <= r && v < st[t].min2) {
            push_min(t, v, tl == tr);
            return;
        }
        pushdown(t, tl, tr);

        int tm = (tl + tr) >> 1;
        update_chmax(l, r, v, t << 1, tl, tm);
        update_chmax(l, r, v, t << 1 | 1, tm + 1, tr);
        merge(t);
    }

    ll query_sum(int l, int r, int t = 1, int tl = 0, int tr = N - 1) {
        if (r < tl || tr < l) { return 0; }
        if (l <= tl && tr <= r) { return st[t].sum; }
        pushdown(t, tl, tr);

        int tm = (tl + tr) >> 1;
        return query_sum(l, r, t << 1, tl, tm) +
            query_sum(l, r, t << 1 | 1, tm + 1, tr);
    }
};



int main(){
    fast;
    ll q,l,r,x,typ;
    cin>>N>>q;
    fore(i,0,N) cin>>a[i];

    STBeats st(N);
    st.build();
    for(int i = 0; i<q; i++){
        cin>>typ>>l>>r;
        r--;
        if (typ == 0){ //[l,r] ai = min(ai,x)
            cin>>x;
            st.update_chmin(l,r,x);
        }
        else if (typ == 1){ //[l,r] ai = max(ai,x)
            cin>>x;
            st.update_chmax(l,r,x);
        }
        else if (typ == 2){ //[l,r] ai += b
            cin>>x;
            st.update_add(l,r,x);
        }
        else if (typ == 3){ //print sum [l,r]
            cout<<st.query_sum(l,r)<<nl;
        }
    }
    return 0;
}


