// Given a sequence a[0], a[1], ... a[n-1], BM, finds the smallest 
// k coefficients c[1], c[2], ... c[k] such that for all valid i:
// a[i] = c[1]*a[i-1] + c[2]*a[i-2] + ... + c[k]*a[i-k] (mod p)

vi bm(vi x){
	vi ls,cur;int lf=0,lk=0;
	fore(i,0,sz(x)){
		ll t=0;
		fore(j,0,sz(cur))t=(t+x[i-j-1]*(ll)cur[j])%mod;
			if((t-x[i])%mod==0)continue;
			if(!sz(cur)){
				cur.resize(i+1);lf=i;lk=(t-x[i])%mod;continue;}
			ll k=-(x[i]-t)*expo(lk,mod-2)%mod; // binary expo
			vi c(i-lf-1);c.pb(k);
			fore(j,0,sz(ls))c.pb(-ls[j]*k%mod);
			if(sz(c)<sz(cur))c.resize(sz(cur));
			fore(j,0,sz(cur))c[j]=(c[j]+cur[j])%mod;
			if(i-lf+sz(ls)>=sz(cur))ls=cur,lf=i,lk=(t-x[i])%mod;
			cur=c;
	}
	fore(i,0,sz(cur))cur[i]=(cur[i]%mod+mod)%mod;
	return cur;
}