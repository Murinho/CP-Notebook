//Lazy propagation (this code): range updates adding a value to all elements, range queries getting the sum of the range [l,r]

#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define nl '\n'

using namespace std;

const ll neut = 0;
const ll lzneut = 0;
vector <ll> a;

void init(ll n){
    a.clear();
    a.assign(n,0LL); //the array is [0, n-1]
}

struct STree { // example: range sum with range addition
	vector<ll> st,lazy;int n;
	STree(int n): st(4*n+5,neut), lazy(4*n+5,lzneut), n(n) {}

	void build(int node, int ini, int fin){
		lazy[node]=0;  // lazy neutral element
		if(ini+1==fin){st[node]=a[ini];return;}
		int mid =(ini+fin)/2;
		build(2*node,ini,mid);
        build(2*node+1,mid,fin);
		st[node]=st[2*node]+st[2*node+1]; // operation
	}
	void push(int node, int ini, int fin){
		if(lazy[node] == lzneut) return; 
		st[node]+=(fin-ini)*lazy[node]; // update st according to lazy
		if(ini+1<fin){ // propagate to children
			lazy[2*node]+=lazy[node];
			lazy[2*node+1]+=lazy[node];
		}
		lazy[node]=0; // clear node lazy
	}
	void upd(int node, int ini, int fin, int l, int r, ll val){
		push(node,ini,fin);
		if(ini>=r||fin <=l)return;
		if(ini>=l&& fin <=r){
			lazy[node]+=val; // accumulate lazy
			push(node,ini,fin);
            return;
		}
		int mid =(ini+fin)/2;
		upd(2*node,ini,mid,l,r,val);upd(2*node+1,mid,fin,l,r,val);
		st[node]=st[2*node]+st[2*node+1]; // operation
	}
	ll query(int node, int ini, int fin, int l, int r){
		if(ini>=r || fin <= l)return neut; // operation neutral
		push(node,ini,fin);
		if(ini>=l&&fin<=r)return st[node];
		int mid =(ini+fin)/2;
		return query(2*node,ini,mid,l,r)+query(2*node+1,mid,fin,l,r); // operation
	}
	void build(){build(1,0,n);} //it is actually [0, n-1]
	void upd(int l, int r, ll val){upd(1,0,n,l,r,val);} //remember the n is non inclusive
	ll query(int l, int r){return query(1,0,n,l,r);} //remember the n is non inclusive
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(s,e,v);rmq.query(s,e);

ll n,q,tc,cmd,l,r,val;

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin>>tc;
    while(tc--){
        cin>>n>>q;
        init(n);
        STree st(n);
        st.build();
        while(q--){
            cin>>cmd>>l>>r;
            l--;
            if (cmd == 0){
                cin>>val;
                st.upd(l,r,val);
            }
            else{
                cout<<st.query(l,r)<<nl;
            }
        }
    }
    return 0;
}