#include <bits/stdc++.h>

using namespace std;

string s,t;
int n,m,dp[1000005],cont,tams,tamt;

void preprocess(){
    int i = 0, j = -1; dp[0] = -1;
    while (i < tamt){
        while (j>= 0 && (t[i] != t[j])){
            j = dp[j];
        }
        i++;
        j++;
        dp[i] = j;
    }
}

void KMP (){
    int i = 0, j = 0;
    while (i<tams){
        while (j>=0 && s[i] != t[j]){
            j = dp[j];
        }
        i++;
        j++;
        if (j == tamt){
            cont++;
            j = dp[j];
        }
    }
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    getline(cin,s); //Base string
    getline(cin,t); //Substring target to look for:
    tams = s.size();
    tamt = t.size();
    cont = 0;
    preprocess();
    KMP();
    cout<<cont<<"\n";
}