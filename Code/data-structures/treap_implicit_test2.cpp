// Tested with: https://www.spoj.com/problems/TAP2014K/
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
#define sz(a) ((ll)a.size())
 
using namespace std;
 
typedef struct Node *pnode;
 
struct Node {
	Node(ll val) : val(val), weight(rand()), size(1), lazy_tag(0) {}
    ll val;
	// ll val, sum;  // val -> a[i], sum = sum of all a[i] in subtree
	ll weight, size;
	bool rev = false;  // whether this range is reversed
	pnode l = nullptr;
    pnode r = nullptr;
	ll lazy_tag; // neutral value is 0.
};
 
int size(pnode node) { return node ? node->size : 0; }
 
// ll sum(pnode node) { return node ? node->sum : 0; }
 
void push(pnode node) {
	if (!node) { return; }
	if (node->rev){  // need to reverse this range
		node->rev = false;
		swap(node->l, node->r);
		if (node->l) { node->l->rev ^= true; }
		if (node->r) { node->r->rev ^= true; }
	}
	if (node->lazy_tag){ // need to update the sum of this range.
		// node->sum += node->lazy_tag * size(node);
        node->val += node->lazy_tag;  // apply the lazy value to this node's val
        node->val %= 26;
		if (node->l) { node->l->lazy_tag += node->lazy_tag;}
		if (node->r) { node->r->lazy_tag += node->lazy_tag;}
		node->lazy_tag = 0;
	}
}
 
void pull(pnode node) {
	if (!node) { return; }
	push(node->l), push(node->r);
	assert(!node->lazy_tag);
	node->size = size(node->l) + size(node->r) + 1;
	// node->sum = sum(node->l) + sum(node->r) + node->val;
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
 
    void swap_intervals(int l1, int r1, int l2, int r2) {
        // Step 1: Split the treap to isolate intervals [l1, r1) and [l2, r2)
        pnode a, b, c, d, e;
        split(root, a, b, l1);         // [0, l1), [l1, n)
        split(b, b, c, r1 - l1);             // [l1, r1), [r1, n)
        split(c, c, d, l2 - r1);             // [r1, l2), [l2, n)
        split(d, d, e, r2 - l2);             // [l2, r2), [r2, n)
 
        // Step 2: Merge back in the order [0, l1) + [l2, r2) + [r1, l2) + [l1, r1) + [r2, n)
        merge(root, a, d);  // [0, l1) + [l2, r2)
        merge(root, root, c);  // + [r1, l2)
        merge(root, root, b);  // + [l1, r1)
        merge(root, root, e);  // + [r2, n)
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
 
    // In-order traversal to print values
	void print_treap(pnode node) {
		if (!node) return;
		push(node);            // Apply any pending updates
		print_treap(node->l);  // Traverse left subtree
		cout << (char)('a' + (node->val%26));  // Convert and print character
		print_treap(node->r);  // Traverse right subtree
	}
 
	void print_all() {
		print_treap(root);
		cout << nl;
	}
};
 
void solve(){
    Treap treap;
    ll val,q,l1,r1,l2,r2;
    string s;
    cin>>s;
    fore(i,0,sz(s)){
        val = (ll)(s[i]-'a');
        treap.insert(i,val);
    }
    cin>>q;
    while(q--){
        cin>>l1>>r1>>l2>>r2;
        l1--, l2--;
        treap.swap_intervals(l1,r1,l2,r2);
        treap.upd(l1, l1 + (r2-l2), [](Node *node) { node->rev ^= true, node->lazy_tag += 1; });
        treap.upd(r2 - (r1-l1), r2, [](Node *node) { node->rev ^= true, node->lazy_tag += 1; });
    } 
    // Print all values:
    treap.print_all();
}
 
int main(){
    fast;
    srand(time(0));
    ll tc;
    cin>>tc;
    while(tc--) solve();
}