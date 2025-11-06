/*
Recurrence:
dp(i,j) = fore(k,0,j+1) dp(i-1)(k-1) + C(k,j)

Look out for:
Prove the monotonocity of opt!! One special case where this
is true is when the cost function satisfies the quadrangle
inequality:
	C(a,c) + C(b,d) <= C(a,d) + C(b,c)
	for all a <= b <= c <= d

Given an array of n elements, your task is to divide into k 
subarrays. The cost of each subarray is the square of the 
sum of the values in the subarray. What is the minimum total 
cost if you act optimally?
*/

const ll maxn = 3015;
const ll inf = 1e18+7;

ll n,a[maxn],dp[maxn][maxn],psum[maxn],k;

void dnc(int i, int l, int r, int optl, int optr){
	if (l > r) return;
	
	int mid = (l+r)/2;
	pii best = {inf,-1};
	for(int j = optl; j < min(mid,optr+1); j++){
		ll sum = psum[mid] - psum[j];
		best = min(best, {dp[i-1][j] + (sum*sum), j});
	}
	
	dp[i][mid] = best.fst;
	int opt = best.snd;
	
	dnc(i,l,mid-1,optl,opt);
	dnc(i,mid+1,r,opt,optr);
}

int main(){
    fast;
    cin >> n >> k;
    fore(i,1,n+1){
    	cin >> a[i];
    	psum[i] = psum[i-1] + a[i];
    }
    
    fore(i,1,n+1) dp[0][i] = inf;
    dp[0][0] = 0;
    
    fore(i,1,k+1){
    	dnc(i,1,n,0,n-1);
    }
    
    cout << dp[k][n] << nl;
    return 0;
}