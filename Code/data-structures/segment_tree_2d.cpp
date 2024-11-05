//Tested with: https://cses.fi/problemset/task/1739/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define nl '\n'
#define fore(i,a,b) for(int i=a;i<b;++i)
 
using namespace std;
 
int n,m;
const int MAXN = 1e3;
int a[MAXN][MAXN],st[2*MAXN][2*MAXN];
char forest[MAXN][MAXN];
const int NEUT = 0;
 
int op(int x, int y){
    return x+y;
}
 
void build(){
	fore(i,0,n)fore(j,0,m)st[i+n][j+m]=a[i][j];
	fore(i,0,n)for(int j=m-1;j;--j)
		st[i+n][j]=op(st[i+n][j<<1],st[i+n][j<<1|1]);
	for(int i=n-1;i;--i)fore(j,0,2*m)
		st[i][j]=op(st[i<<1][j],st[i<<1|1][j]);
}
void upd(int x, int y, int v){
	st[x+n][y+m]=v;
	for(int j=y+m;j>1;j>>=1)st[x+n][j>>1]=op(st[x+n][j],st[x+n][j^1]);
	for(int i=x+n;i>1;i>>=1)for(int j=y+m;j;j>>=1)
		st[i>>1][j]=op(st[i][j],st[i^1][j]);
}
int query(int x0, int y0, int x1, int y1){
	int r=NEUT;
	for(int i0=x0+n,i1=x1+n;i0<i1;i0>>=1,i1>>=1){
		int t[4],q=0;
		if(i0&1)t[q++]=i0++;
		if(i1&1)t[q++]=--i1;
		fore(k,0,q)for(int j0=y0+m,j1=y1+m;j0<j1;j0>>=1,j1>>=1){
			if(j0&1)r=op(r,st[t[k]][j0++]);
			if(j1&1)r=op(r,st[t[k]][--j1]);
		}
	}
	return r;
}
 
ll q,cmd,x,y,x2,y2;
 
int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin>>n>>q;
	m = n;
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
			cin>>forest[i][j];
			if (forest[i][j] == '.') a[i][j] = 0;
			else a[i][j] = 1;
		}
    }
	build();
	while(q--){
		cin>>cmd>>x>>y;
		x--, y--;
		if (cmd == 1){
			if (forest[x][y] == '.'){
				forest[x][y] = '*';
				upd(x,y,1);
			}
			else{
				forest[x][y] = '.';
				upd(x,y,0);
			}
		}
		else{
			cin>>x2>>y2;
			cout<<query(x,y,x2,y2)<<nl;
		}
	}
    //cout<<query(0,0,4,4)<<"\n"; //(x,y) inclusive, (x1,y1) exclusive (excluding that row and column).
    return 0;
}