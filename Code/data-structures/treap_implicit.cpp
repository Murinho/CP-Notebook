typedef struct Node *pnode;

const ll maxn = 1e6+10;

struct Node {
	Node(ll val) : val(val), weight(rand()), size(1), lazy_tag(0) {}
	ll val, sum;  // val -> a[i], sum = sum of all a[i] in subtree
	ll weight, size;
	bool rev = false;  // whether this range is reversed
	pnode l = nullptr;
	pnode r = nullptr;
	ll lazy_tag; // neutral value is 0.
};
 
int size(pnode node) { return node ? node->size : 0; }
 
ll sum(pnode node) { return node ? node->sum : 0; }
 
void push(pnode node) {
	if (!node) { return; }
	if (node->rev){  // need to reverse this range
		node->rev = false;
		swap(node->l, node->r);
		if (node->l) { node->l->rev ^= true; }
		if (node->r) { node->r->rev ^= true; }
	}
	if (node->lazy_tag){ // need to update the sum of this range.
		node->sum += node->lazy_tag * size(node);
		node->val += node->lazy_tag; 
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
 
	void swap_intervals(int l1, int r1, int l2, int r2) {
		if (l1 > l2) {
			swap(l1, l2);
			swap(r1, r2);
		}
		assert(r1 <= l2);

		pnode a, b, c, d, e;
		split(root, a, b, l1);
		split(b, b, c, r1 - l1);
		split(c, c, d, l2 - r1);
		split(d, d, e, r2 - l2);
 
		merge(root, a, d);
		merge(root, root, c);
		merge(root, root, b);
		merge(root, root, e);
	}
 
	// updates the range [l, r)
	void upd(int l, int r, function<void(Node *)> f) {
		Node *a, *b, *c;
		split(root, a, b, l);
		split(b, b, c, r - l);
		if (b) { f(b); }
		// merge all the splits back into the main treap
		merge(root, a, b);
		merge(root, root, c);
	}
	// queries the range [l,r)
	template <typename R> R query(int l, int r, function<R(Node *)> f) {
		Node *a, *b, *c;
		split(root, a, b, l);
		split(b, b, c, r - l);
		assert(b);
		R x = f(b);
		merge(root, a, b);
		merge(root, root, c);
		return x;
	}

	void print_treap(pnode node) {
		if (!node) return;
		push(node);            
		print_treap(node->l);  
		cout<<node->val<<" ";
		print_treap(node->r); 
	}
 
	void print_all() {
		print_treap(root);
		cout << nl;
	}
};
 
void doit() {
	int pos, val, l, r, x;
	Treap treap;
	// insert:
	treap.insert(pos, val);
	// delete:
	treap.del(pos);
	// update [l, r) reverse:
	treap.upd(l, r, [](Node *node) { node->rev ^= true; });
	// update [l, r) adding a value x:
	treap.upd(l, r, [x](Node *node) { node->lazy_tag += x; });
	// query for the sum in [l, r)
	ll range_sum = treap.query<ll>(l, r, [](Node *node) { return node->sum; });
}

int main(){ srand(time(0)); }
