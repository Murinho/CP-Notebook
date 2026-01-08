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

static const ld EPS_F   = 1e-12L; // function near-zero
static const ld EPS_DUP = 1e-8L;  // root dedup tolerance

// Horner evaluation: a[0] + a[1]x + ... + a[n]x^n
ld eval_poly(const vector<ld>& a, ld x) {
    ld res = 0;
    for (int i = (int)a.size() - 1; i >= 0; --i)
        res = res * x + a[i];
    return res;
}

// Derivative coefficients
vector<ld> derivative(const vector<ld>& a) {
    int n = (int)a.size() - 1;
    if (n <= 0) return {0};
    vector<ld> d(n);
    for (int i = 1; i <= n; ++i) d[i - 1] = a[i] * (ld)i;
    return d;
}

// Cauchy root bound: all roots in [-B, B]
ld root_bound(const vector<ld>& a) {
    int n = (int)a.size() - 1;
    ld an = fabsl(a[n]);
    if (an == 0) return 0;
    ld mx = 0;
    for (int i = 0; i < n; ++i) mx = max(mx, fabsl(a[i]) / an);
    return 1 + mx;
}

// Bisection on [l, r] assuming a sign change (or near-zero endpoint)
ld bisect_root(const vector<ld>& a, ld l, ld r) {
    ld fl = eval_poly(a, l);
    ld fr = eval_poly(a, r);

    if (fabsl(fl) < EPS_F) return l;
    if (fabsl(fr) < EPS_F) return r;

    // Ensure fl and fr have opposite signs
    // (Caller should guarantee this; still handle numerics defensively)
    for (int it = 0; it < 200; ++it) {
        ld m = (l + r) / 2;
        ld fm = eval_poly(a, m);

        if (fabsl(fm) < EPS_F) return m;

        // Decide which side keeps a sign change
        if ((fl > 0 && fm < 0) || (fl < 0 && fm > 0)) {
            r = m; fr = fm;
        } else {
            l = m; fl = fm;
        }

        if (fabsl(r - l) < 1e-15L) break;
    }
    return (l + r) / 2;
}

// Remove leading highest-degree zeros (in case)
void trim(vector<ld>& a) {
    while (a.size() > 1 && fabsl(a.back()) < 1e-18L) a.pop_back();
}

// Input polynomial coeffs. a[0], a[1], ... a[n]
// Output: returns all real roots (unique, sorted)
vector<ld> all_real_roots(vector<ld> a) { 
    trim(a);
    int n = (int)a.size() - 1;

    if (n <= 0) return {}; // constant (ignore)
    if (n == 1) {
        // a0 + a1 x = 0
        if (fabsl(a[1]) < 1e-18L) return {};
        return { -a[0] / a[1] };
    }

    // 1) get critical points from derivative
    vector<ld> d = derivative(a);
    vector<ld> crit = all_real_roots(d);
    sort(crit.begin(), crit.end());

    // 2) bound the search region
    ld B = root_bound(a);
    // small padding to avoid boundary issues
    ld L = -B - 1, R = B + 1;

    // 3) Build partition points: L, crit..., R
    vector<ld> pts;
    pts.reserve(crit.size() + 2);
    pts.push_back(L);
    for (ld x : crit) pts.push_back(x);
    pts.push_back(R);

    // 4) Collect roots:
    vector<ld> roots;

    // (a) roots in monotone intervals via sign change
    for (int i = 0; i + 1 < (int)pts.size(); ++i) {
        ld l = pts[i], r = pts[i + 1];

        ld fl = eval_poly(a, l);
        ld fr = eval_poly(a, r);

        // If either endpoint is (numerically) a root, record it.
        if (fabsl(fl) < EPS_F) roots.push_back(l);
        if (fabsl(fr) < EPS_F) roots.push_back(r);

        // sign change => exactly one root in (l, r)
        if ((fl > 0 && fr < 0) || (fl < 0 && fr > 0)) {
            roots.push_back(bisect_root(a, l, r));
        }
    }

    // (b) even-multiplicity roots happen at critical points: check them directly
    for (ld c : crit) {
        ld fc = eval_poly(a, c);
        if (fabsl(fc) < 1e-10L) roots.push_back(c);
    }

    // 5) Sort + deduplicate (collapse near-equal roots)
    sort(roots.begin(), roots.end());
    vector<ld> uniq;
    for (ld x : roots) {
        if (uniq.empty() || fabsl(x - uniq.back()) > EPS_DUP) uniq.push_back(x);
        else {
            // average to stabilize a bit
            uniq.back() = (uniq.back() + x) / 2;
        }
    }

    return uniq;
}