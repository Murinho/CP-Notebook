// Tested with: https://cses.fi/problemset/task/1110/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ld long double
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(ll i=a; i<b; i++)
#define rofe(i,a,b) for(ll i=a-1; i>=b; i--)
#define ALL(u) u.begin(),u.end()
#define vi vector <ll>
#define vvi vector <vi>
#define sz(a) ((ll)a.size())
#define lsb(x) ((x)&(-x))
#define PI acos(-1.0)
#define pii pair <ll,ll>
#define fst first
#define snd second
#define RB(x) (x<n?r[x]:0)

using namespace std;

string duvalMinShift(string s){ // finds the minimum cyclic shift of a string.
    s += s;
    int i = 0, ans = 0;
    while (i < sz(s) / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < sz(s) && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else k++;
            j++;
        }
        while (i <= k) i += j - k;
    }
    return s.substr(ans, sz(s) / 2);
}

int main(){
    fast;
    string s;
    cin>>s;
    cout<<duvalMinShift(s)<<nl;
    return 0;
}