void dnc(int i, int l, int r, int optl, int optr){
	if (l > r) return;
	
	int mid = (l+r)/2;
	pii best = {inf,-1};
	for(int j = optl; j < min(mid,optr+1); j++){
		ll sum = psum[mid] - psum[j]; // minimize sum of squares
		best = min(best, {dp[i-1][j] + (sum*sum), j});
	}
	
	dp[i][mid] = best.fst;
	int opt = best.snd;
	
	dnc(i,l,mid-1,optl,opt);
	dnc(i,mid+1,r,opt,optr);
}