const int maxn = 1005;
int dp[maxn][maxn];
int lcs(const string &s, const string &t){
    int n = sz(s), m = sz(t);
    fore(j,0,m+1) dp[0][j] = 0;
    fore(i,0,n+1) dp[i][0] = 0;
    fore(i,1,n+1){
        fore(j,1,m+1){
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            if (s[i-1] == t[j-1]){
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
            }
        }
    }
    return dp[n][m];
}