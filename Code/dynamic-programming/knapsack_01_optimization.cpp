/*  0/1 Knapsack optimization where sum of all items is ~ N
    There will be at most sqrt(N) different items.
    Array 'cnt' represents the count of a specific item.
*/

const ll maxn = 1e5+50;
const ll maxnsq = 400;

ll n,m,cnt[maxn],dp[maxnsq][maxn];
vi c;
void calculateDp(){ //DP in O(N*sqrt(N))
    dp[0][0]=0;
    fore(i,1,n+5) dp[0][i] = -1;
    fore(i,1,sz(c)){ // c is the array of unique items.
        fore(j,1,n+1){
            if(dp[i-1][j] >= 0)
                dp[i][j] = 0;
            else if(j-c[i] >= 0 && dp[i][j - c[i]] >= 0 and dp[i][j - c[i]] < cnt[c[i]])
                dp[i][j] = dp[i][j - c[i]] + 1;
            else
                dp[i][j] = -1;
        }
    }
}