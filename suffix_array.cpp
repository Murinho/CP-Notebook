#include <bits/stdc++.h>
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
#define RB(x) (x<n?r[x]:0)
#define nl '\n'

using namespace std;

void csort(vector<int>& sa, vector<int>& r, int k){
	int n=sa.size();
	vector<int> f(max(255,n),0),t(n);
	fore(i,0,n)f[RB(i+k)]++;
	int sum=0;
	fore(i,0,max(255,n))f[i]=(sum+=f[i])-f[i];
	fore(i,0,n)t[f[RB(sa[i]+k)]++]=sa[i];
	sa=t;
}
vector<int> constructSA(string& s){
	int n=s.size(),rank;
	vector<int> sa(n),r(n),t(n);
	fore(i,0,n)sa[i]=i,r[i]=s[i];
	for(int k=1;k<n;k*=2){
		csort(sa,r,k);csort(sa,r,0);
		t[sa[0]]=rank=0;
		fore(i,1,n){
			if(r[sa[i]]!=r[sa[i-1]]||RB(sa[i]+k)!=RB(sa[i-1]+k))rank++;
			t[sa[i]]=rank;
		}
		r=t;
		if(r[sa[n-1]]==n-1)break;
	}
	return sa;
}

int main()
{   
    string s;
    int k;
    cin>>s>>k;
	s = "$" + s; //add an extra symbol at the beginning to avoid conflicts.
    vector <int> sa = constructSA(s);
    for (auto au : sa) cout<<au<<" ";
    cout<<nl;
}