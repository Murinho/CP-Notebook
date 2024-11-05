//Computes the longest palindrome.
#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

using namespace std;

const ll MAXN = 1e6+5;
int d1[MAXN];//d1[i] = max odd palindrome centered on i
int d2[MAXN];//d2[i] = max even palindrome centered on i

//s  aabbaacaabbaa
//d1 1111117111111
//d2 0103010010301
void manacher(string& s){
	int l=0,r=-1,n=s.size();
	fore(i,0,n){
		int k=i>r?1:min(d1[l+r-i],r-i);
		while(i+k<n&&i-k>=0&&s[i+k]==s[i-k])k++;
		d1[i]=k--;
		if(i+k>r)l=i-k,r=i+k;
	}
	l=0;r=-1;
	fore(i,0,n){
		int k=i>r?0:min(d2[l+r-i+1],r-i+1);k++;
		while(i+k<=n&&i-k>=0&&s[i+k-1]==s[i-k])k++;
		d2[i]=--k;
		if(i+k-1>r)l=i-k,r=i+k-1;
	}
}

int main(){
    fast;
    int best = 0;
    bool even = false;
    int pos = 0;
    int stpos,tope;
    string s,ans = "";
    cin>>s;
    manacher(s);
	int r=0;
    //Check odd palindromes.
    fore(i,0,s.size()){
        if (2*d1[i] - 1 > best){
            best = 2*d1[i] - 1;
            pos = i;
        }
    }
    //Check even palindromes.
    fore (i,0,s.size()){
        if (2*d2[i] > best){
            best = 2*d2[i];
            pos = i;
            even = true;
        }
    }
    if (!even) stpos = pos-d1[pos]+1; 
    else stpos = pos-d2[pos];

    tope = stpos+best-1;
    
    for (int i = stpos; i<=tope; i++) ans += s[i];
    cout<<ans<<nl;
	return 0;
}