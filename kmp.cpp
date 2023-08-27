#include <bits/stdc++.h>
#define ll long long
#define nl '\n'

using namespace std;

vector<int> kmp(string s){
    int n = s.size();
    vector<int> vs(n);
 
    for(int i=1; i<n; i++){
        int j = vs[i-1];
        while(j!=0 && s[i] != s[j]){
            j = vs[j-1];
        }
        if(s[i] == s[j]) j++;
        vs[i] = j;
    }
    return vs;
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    string s,t;
    getline(cin,s); //Base string
    getline(cin,t); //Substring target to look for:
    ll tamt = t.size();
    t += "#";
    s = t + s;
    vector <int> res = kmp(s);
    ll ans = 0;
    for (auto au : res){
        if (au == tamt-1) ans++;
    }
    cout<<ans<<nl;
    return 0;
}