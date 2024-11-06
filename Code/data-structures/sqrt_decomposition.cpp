const int maxn = 5e5+10;
const int block_amount = 710; // block_amount squared should be > maxn.
vi b[710]; //blocks of the SQRT.
int a[maxn];
int n,bsize;

void build_blocks(){
    bsize = sqrt(n)+1;
    fore(i,0,n) b[i/bsize].pb(a[i]);

    fore(i,0,bsize+1) sort(ALL(b[i])); //sort the blocks.
}

ll query(int l, int r, ll x){ // in [l,r] get amount of values >= x.
    int ans=0;
    int cl = l/bsize;
    int cr = r/bsize;
    if (cl == cr){
        fore(i,l,r+1){
            if (x <= a[i]) ans++;
        }
    }
    else{
        fore(i,l,(cl+1)*bsize){ //get prefix:
            if (x <= a[i]) ans++;
        }
        fore(i,cl+1,cr){ //mid part:
            ans += (sz(b[i]) - (lower_bound(ALL(b[i]),x) - b[i].begin()));
        }
        fore(i,cr*bsize,r+1){ //get suffix:
            if (x <= a[i]) ans++;
        }
    }
    return ans;
}

void update(int pos, ll x){ // point update in O(bsize)
    int cb = pos/bsize;
    int idx = lower_bound(ALL(b[cb]),a[pos]) - b[cb].begin();
    b[cb][idx] = a[pos] = x;
    sort(ALL(b[cb]));
}