#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a;i<b;++i)
#define ALL(s) s.begin(),s.end()
#define vi vector <ll>
#define vvi vector<vi>
#define PI 3.1415926535
    
    
using namespace std;

vector <int> phi;

//Amount of coprime numbers (gcd(a,b) == 1) for each number in (1 <= i <= n).
//counting the number of integers between 1 and i, which are coprime to i.
void euler_totient(int n) { 
    phi.resize(n+1);
    for (int i = 0; i <= n; i++) phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

//Amount of numbers 0 <= i < m such that gcd(a+i,m) == gcd(a,m)
int phiFunc(int a, int m) { 
    ll y = m/__gcd(a,m);
    ll ans = y;
    for(ll i = 2; i*i<=m; i++){
        if (y%i == 0){
            ans -= ans/i;
            while(y%i == 0) y /= i;
        }
    }
    if (y>1) ans -= ans/y;
    return ans;
}


int main(){
    int n;
    cin>>n;
    euler_totient(n);
    fore(i,1,n+1) cout<<phi[i]<<" ";
    cout<<nl;
    return 0;
}