// Tested with AC: https://judge.yosupo.jp/problem/range_kth_smallest
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
#define eb emplace_back
#define ppb pop_back
#define i128 __int128_t
#define ull unsigned long long
 
using namespace std;
 
struct WaveletTree {
    int lo, hi;
    WaveletTree *L = nullptr, *R = nullptr;
    vi mapLeft;

    WaveletTree() = default;

    WaveletTree(const vi &arr, int lo, int hi) : lo(lo), hi(hi) {
        if (!sz(arr) || lo == hi) return;
        int mid = (lo + hi) >> 1;
        mapLeft.reserve(sz(arr) + 1);
        mapLeft.pb(0);

        vi leftArr; leftArr.reserve(sz(arr));
        vi rightArr; rightArr.reserve(sz(arr));
        for (int v : arr) {
            bool goLeft = (v <= mid);
            mapLeft.pb(mapLeft.back() + (goLeft ? 1 : 0));
            (goLeft ? leftArr : rightArr).pb(v);
        }
        if (sz(leftArr))  L = new WaveletTree(leftArr, lo, mid);
        if (sz(rightArr)) R = new WaveletTree(rightArr, mid + 1, hi);
    }

    // count in [l..r] whose compressed value in [x..y]
    int count_comp(int l, int r, int x, int y) const {
        if (!this || l > r || x > y || y < lo || x > hi) return 0;
        if (x <= lo && hi <= y) return r - l + 1;
        int lb = mapLeft[l - 1], rb = mapLeft[r];
        int lL = lb + 1, rL = rb;
        int lR = (l - lb), rR = (r - rb);
        return (L ? L->count_comp(lL, rL, x, y) : 0) + (R ? R->count_comp(lR, rR, x, y) : 0);
    }

    // k-th (1-indexed) in [l..r], returns compressed id in [lo..hi]
    int kth_comp(int l, int r, int k) const {
        // assumes 1 <= k <= r-l+1
        if (lo == hi) return lo;
        int lb = mapLeft[l - 1], rb = mapLeft[r];
        int inLeft = rb - lb;
        if (k <= inLeft) return L->kth_comp(lb + 1, rb, k);
        return R->kth_comp(l - lb, r - rb, k - inLeft);
    }

    ~WaveletTree() { delete L; delete R; }
};

struct WaveletIndex {
    vi a;
    vi compVals;  // sorted unique original values
    vi a_comp;    // 1..σ
    unique_ptr<WaveletTree> root;

    // Pass the array of size n [0,n-1], without trailing unused spaces, then it'll be 1-indexed
    explicit WaveletIndex(const vi &arr) {
        a = arr;
        compVals = arr;
        sort(ALL(compVals));
        compVals.erase(unique(ALL(compVals)), compVals.end());
        a_comp.resize(sz(a));
        for (int i = 0; i < sz(a); i++) {
        a_comp[i] = int(lower_bound(ALL(compVals), a[i]) - compVals.begin()) + 1;
        }
        root = make_unique<WaveletTree>(a_comp, 1, (int)compVals.size());
    }

    int compress_floor_idx(int v) const {
        auto it = upper_bound(ALL(compVals), v);
        if (it == compVals.begin()) return 0;
        return int(it - compVals.begin());
    }
    int compress_ceil_idx(int v) const {
        auto it = lower_bound(ALL(compVals), v);
        if (it == compVals.end()) return (int)compVals.size() + 1;
        return int((it - compVals.begin()) + 1);
    }

    // count values in [l..r] with original values in [x..y]
    int count(int l, int r, int x, int y) const {
        if (l > r) swap(l, r);
        if (x > y) swap(x, y);
        l = max(l, 1); r = min(r, (int)a.size());
        if (l > r) return 0;
        int cy = compress_floor_idx(y);      // last comp id <= y   (0..σ)
        int cx = compress_ceil_idx(x);       // first comp id >= x  (1..σ+1)
        if (cx > cy) return 0;
        return root->count_comp(l, r, cx, cy);
    }

    // k-th smallest in [l..r] (1-indexed k). Returns original value.
    int kth_smallest(int l, int r, int k) const {
        if (l > r) swap(l, r);
        l = max(l, 1); r = min(r, (int)a.size());
        int len = r - l + 1;
        if (l > r || k < 1 || k > len) return INT_MIN;
        int comp_id = root->kth_comp(l, r, k);
        return compVals[comp_id - 1];
    }

    // k-th largest in [l..r] (1-indexed k). Returns original value.
    int kth_largest(int l, int r, int k) const {
        if (l > r) swap(l, r);
        l = max(l, 1); r = min(r, (int)a.size());
        int len = r - l + 1;
        if (l > r || k < 1 || k > len) return INT_MIN;

        return kth_smallest(l, r, len - k + 1);
    }
};

int main() {
    fast;
    int n, q;
    cin >> n >> q;
    vi arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    WaveletIndex wt(arr);

    while (q--) {
        ll l, r, k;
        cin >> l >> r >> k;
        l++;
        k++;
        cout << wt.kth_smallest(l, r, k) << '\n';
    }
    return 0;
}