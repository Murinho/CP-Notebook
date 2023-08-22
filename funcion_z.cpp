//Z Function for strings (longest prefix from start and from i).
//Complexity O(n).

#include <bits/stdc++.h>
#define ll long long 
#define pb push_back

using namespace std;

ll n;
string s;
vector <int> z;

void init(){
    n = s.size();
    z.resize(n);
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin>>s;
    init();
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r){
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]){
            z[i]++;
        }
        if (i + z[i] - 1 > r){
            l = i, r = i + z[i] - 1;
        }
    }
    //Printing the values of Z function:
    for (int i = 0; i<n; i++) cout<<z[i]<<" ";
    cout<<"\n";
    return 0;
}