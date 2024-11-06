//Tested with: https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
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

typedef struct Node *pnode;

const ll maxn = 1e6+10;

struct mint {
	const static int M = 998244353;
	ll v = 0;
	mint() {}
	mint(ll v) { this->v = (v % M + M) % M; }
	mint operator+(const mint &o) const { return v + o.v; }
	mint &operator+=(const mint &o) {
		v = (v + o.v) % M;
		return *this;
	}
	mint operator*(const mint &o) const { return v * o.v; }
	mint operator-(const mint &o) const { return v - o.v; }
	mint &operator-=(const mint &o) {
		mint t = v - o.v;
		v = t.v;
		return *this;
	}
	mint operator^(int y) const {
		mint r = 1, x = v;
		for (y <<= 1; y >>= 1; x = x * x)
			if (y & 1) r = r * x;
		return r;
	}
	mint inv() const {
		assert(v);
		return *this ^ M - 2;
	}
	friend istream &operator>>(istream &s, mint &v) {
		return s >> v.v;
		return s;
	}
	friend ostream &operator<<(ostream &s, const mint &v) { return s << v.v; }
	mint operator/(mint o) { return *this * o.inv(); }
};

struct Line {  // linear function wx + b
	mint w = 1, b = 0;
	mint operator()(mint x) { return w * x + b; }
	Line operator()(Line f) { return Line{w * f.w, w * f.b + b}; }
	operator bool() const {
		return w.v != 1 || b.v != 0;
	}  // false if this is identity function
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
	Node(mint val) : val(val), sum(val), weight(rng()), size(1) {}
	mint val, sum;  // val -> a[i], sum = sum of all a[i] in subtree
	ll weight, size;
	bool rev = false;  // whether this range is reversed
	pnode l = nullptr;
    pnode r = nullptr;
	Line f;  // lazy affine tag
};

int size(pnode node) { return node ? node->size : 0; }

mint sum(pnode node) { return node ? node->sum : 0; }

void push(pnode node) {
	if (!node) { return; }
	if (node->rev) {  // need to reverse this range
		node->rev = false;
		swap(node->l, node->r);
		if (node->l) { node->l->rev ^= true; }
		if (node->r) { node->r->rev ^= true; }
	}
	if (node->f) {  // need to affine this range
		node->val = node->f(node->val);
		node->sum = node->f.w * node->sum + node->f.b * node->size;
		if (node->l) { node->l->f = node->f(node->l->f); }
		if (node->r) { node->r->f = node->f(node->r->f); }
		node->f = Line{1, 0};
	}
}

void pull(pnode node) {
	if (!node) { return; }
	push(node->l), push(node->r);
	assert(!node->f);
	node->size = size(node->l) + size(node->r) + 1;
	node->sum = sum(node->l) + sum(node->r) + node->val;
}

// merges treaps l and r into treap
void merge(pnode &node, pnode l, pnode r) {
	push(l), push(r);
	if (!l || !r) {
		node = l ? l : r;
	} else if (l->weight > r->weight) {
		merge(l->r, l->r, r), node = l;
	} else {
		merge(r->l, l, r->l), node = r;
	}
	pull(node);
}

// splits treap into l, r; l: [0, val), r: [val, )
void split(pnode node, pnode &l, pnode &r, int val) {
	if (!node) return void(l = r = nullptr);
	push(node);
	if (val > size(node->l)) {
		split(node->r, node->r, r, val - size(node->l) - 1), l = node;
	} else {
		split(node->l, l, node->l, val), r = node;
	}
	pull(node);
}

struct Treap {
	Node *root = nullptr;  // root of this treap

	void insert(int i, int x) {
		Node *l, *r;
		split(root, l, r, i);
		auto v = new Node(x);
		merge(l, l, v);
		merge(root, l, r);
	}

	void del(int i) {
		Node *l, *r;
		split(root, l, r, i);
		split(r, root, r, 1);
		merge(root, l, r);
	}

	/**
	 * updates the range [l, r)
	 * @param f the function to apply to the range
	 */
	void upd(int l, int r, function<void(Node *)> f) {
		Node *a, *b, *c;  // a: [0, l); b: [l, r); c: [r, )
		split(root, a, b, l);
		split(b, b, c, r - l);
		if (b) { f(b); }
		// merge all the splits back into the main treap
		merge(root, a, b);
		merge(root, root, c);
	}

	/**
	 * queries the range [l, r)
	 * @param f a query function (see use below)
	 */
	template <typename R> R query(int l, int r, function<R(Node *)> f) {
		Node *a, *b, *c;  // a: [0, l); b: [l, r); c: [r, )
		split(root, a, b, l);
		split(b, b, c, r - l);
		assert(b);
		R x = f(b);
		merge(root, a, b);
		merge(root, root, c);
		return x;
	}
};

int main() {
	int n,q;
	cin>>n>>q;
	Treap treap;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		treap.insert(i, x);
	}

    while(q--){
        int t;
		cin >> t;
		int i, x, l, r, w, b;
		switch (t) {
		case 0:
			cin >> i >> x;
			treap.insert(i, x);
			break;
		case 1:
			cin >> i;
			treap.del(i);
			break;
		case 2:
			cin >> l >> r;
			treap.upd(l, r, [](Node *x) { x->rev ^= true; });
			break;
		case 3:
			cin >> l >> r >> w >> b;
			treap.upd(l, r, [=](Node *x) { x->f = Line{w, b}(x->f); });
			break;
		case 4:
			cin >> l >> r;
			cout <<treap.query<mint>(l, r, [](Node *x) { return x->sum; })<< nl;
			break;
		}
    }
}