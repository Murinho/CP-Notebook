#include <bits/stdc++.h>
#define ll long long 
#define pb push_back

using namespace std;

const ll mod = 1e18+7;
vector < vector <ll> > a,b,mat;
ll k,pot,ans;
bool flag;

void clean(){
    a.resize(2);
    b.resize(2);
    mat.resize(2);
    flag = false;
    for (int i = 0; i<=1; i++) a[i].resize(2), b[i].resize(2), mat[i].resize(2);
}

void exponentiate(){
    //cout<<"Expo: \n";
    b = a;
    for (int i = 0; i<=1; i++){
        for (int j = 0; j<=1; j++){
            ll val = 0;
            for (int x = 0; x<=1; x++) val = (val + ((b[i][x]*b[x][j])%mod))%mod;
            a[i][j] = val;
          //  cout<<a[i][j]<<" ";
        }
        //cout<<"\n";
    }
}

void multiply(){
    b = mat;
    for (int i = 0; i<=1; i++){
        for (int j = 0; j<=1; j++){
            ll val = 0;
            for (int x = 0; x<=1; x++) val = (val + ((b[i][x]*a[x][j])%mod))%mod;
            mat[i][j] = val;
        }
    }
}

int main(){
    cin>>k; //The index of the fibonacci sequence we want to look.
    k--;
    clean();
    pot = 1;
    a[0][0] = 1;
    a[0][1] = 1;
    a[1][0] = 1;
    a[1][1] = 0;
    for (int i = 0; i<8; i++){
        ll aux = pot & k;
        if (aux == pot){
            if (!flag){
                mat = a;
                flag = true;
            }
            else multiply();
        }
        exponentiate();
        pot *= 2;
    }
    ans = mat[1][0] + mat[1][1];
    cout<<ans<<endl;
}