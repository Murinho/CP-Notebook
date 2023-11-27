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

void euler_totient(int n) { //Amount of coprime numbers (gcd(a,b) == 1) to each number in (1 <= i <= n).
    phi.resize(n+1);
    for (int i = 0; i <= n; i++) phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}


int main(){
    int n;
    cin>>n;
    euler_totient(n);
    fore(i,1,n+1) cout<<phi[i]<<" ";
    cout<<nl;
    return 0;
}