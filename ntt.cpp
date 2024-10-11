//Tested with: https://codeforces.com/problemset/problem/1096/G
#include <bits/stdc++.h>
#define ll long long
#define fore(i,a,b) for(ll i=a; i<b; i++)
#define nl '\n'
#define pb push_back
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector<vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second

using namespace std;

// MAXN must be power of 2 !!
// MOD-1 needs to be a multiple of MAXN !!
// big mod and primitive root for NTT:
const int MOD=998244353,RT=3,MAXN=1<<21;
const int loga = 17;
typedef vector<ll> poly;

int mulmod(ll a, ll b){return a*b%MOD;}
int addmod(int a, int b){int r=a+b;if(r>=MOD)r-=MOD;return r;}
int submod(int a, int b){int r=a-b;if(r<0)r+=MOD;return r;}
int pm(ll a, ll e){
	int r=1;
	while(e){
		if(e&1)r=mulmod(r,a);
		e>>=1;a=mulmod(a,a);
	}
	return r;
}
int inv(int a){return pm(a,MOD-2);}

struct CD {
	int x;
	CD(int x):x(x){}
	CD(){}
	int get()const{return x;}
};
CD operator*(const CD& a, const CD& b){return CD(mulmod(a.x,b.x));}
CD operator+(const CD& a, const CD& b){return CD(addmod(a.x,b.x));}
CD operator-(const CD& a, const CD& b){return CD(submod(a.x,b.x));}
vector<int> rts(MAXN+9,-1);
CD root(int n, bool inv){
	int r=rts[n]<0?rts[n]=pm(RT,(MOD-1)/n):rts[n];
	return CD(inv?pm(r,MOD-2):r);
}
CD cp1[MAXN+9],cp2[MAXN+9];
int R[MAXN+9];
void dft(CD* a, int n, bool inv){
	fore(i,0,n)if(R[i]<i)swap(a[R[i]],a[i]);
	for(int m=2;m<=n;m*=2){
		CD wi=root(m,inv);
		for(int j=0;j<n;j+=m){
			CD w(1);
			for(int k=j,k2=j+m/2;k2<j+m;k++,k2++){
				CD u=a[k];CD v=a[k2]*w;a[k]=u+v;a[k2]=u-v;w=w*wi;
			}
		}
	}
	if(inv){ 
		CD z(pm(n,MOD-2));
		fore(i,0,n)a[i]=a[i]*z;
	}
}
poly multiply(poly& p1, poly& p2){
	int n=p1.size()+p2.size()+1;
	int m=1,cnt=0;
	while(m<=n)m+=m,cnt++;
	fore(i,0,m){R[i]=0;fore(j,0,cnt)R[i]=(R[i]<<1)|((i>>j)&1);}
	fore(i,0,m)cp1[i]=0,cp2[i]=0;
	fore(i,0,p1.size())cp1[i]=p1[i];
	fore(i,0,p2.size())cp2[i]=p2[i];
	dft(cp1,m,false);dft(cp2,m,false);
	fore(i,0,m)cp1[i]=cp1[i]*cp2[i];
	dft(cp1,m,true);
	poly res;
	n-=2;
	fore(i,0,n)res.pb(cp1[i].x);
	return res;
}


ll n,k;

poly exponentiate(poly b, ll pw){
    poly expo = b;
    ll pot = 1;
    poly res = {1};
    fore(i,0,loga){
        if ((pot|pw) == pw){
            while(sz(res)<sz(expo)) res.pb(0);
            while(sz(expo)<sz(res)) expo.pb(0);
            res = multiply(res,expo);
        }
        expo = multiply(expo,expo);
        pot *= 2;
    }
    return res;
}

int main(){
    fast;
    cin>>n>>k;
    poly a(10,0);
    fore(i,0,k){
        ll x;
        cin>>x;
        a[x]=1;
    }
    n /= 2;
    poly v = exponentiate(a,n);

    ll ans=0;
    for(auto au : v){
        if (au>0){
            ans = (ans + ((au*au)%MOD))%MOD;
        }
    }
    cout<<ans<<nl;
    return 0;
}