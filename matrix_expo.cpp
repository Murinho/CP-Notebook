#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

ll n,num,k;
vector < vector <ll> > mat,a,b;
bool flag = false;

void clean(){
    a.clear();
    a.resize(n+1);
    b.clear();
    b.resize(n+1);
    mat.clear();
    mat.resize(n+1);
    flag = false;
    for (int i = 1; i<=n; i++) mat[i].resize(n+1), a[i].resize(n+1), b.resize(n+1); 
}

void upgrade(){
    b = a;
    for (int i = 1; i<=n; i++){
        for (int j = 1; j<=n; j++){
            ll val = 0;
            for (int x = 1; x<=n; x++) val += (b[i][x] * b[x][j]);
            a[i][j] = val;
        }
    }
}

void exponentiate(){
    b = mat;
    for (int i = 1; i<=n; i++){
        for (int j = 1; j<=n; j++){
            ll val = 0;
            for (int x = 1; x<=n; x++) val += (b[i][x]*a[x][j]);
            mat[i][j] = val;
        }
    }
}

int main(){
    cin.tie(0);
    cout.tie(0);
    //Size of the n*n matrix, and 'k', the desired power.
    cin>>n>>k;
    clean();
    for (int i = 1; i<=n; i++){
        for (int j = 1; j<=n; j++){
            cin>>mat[i][j];
            a[i][j] = mat[i][j];
        }
    }
    ll pot = 1;
    while(pot <= k){
        ll aux = pot & k;
        if (aux == pot){
            if (!flag){
                mat = a;
                flag = true;
            }
            else exponentiate();
        }
        upgrade();
        pot *= 2;
    }
    ll sum = 0;
    for (int i = 1; i<=n; i++){
        for (int j = 1; j<=n; j++){
            cout<<mat[i][j]<<" ";
            if (i == j) sum += mat[i][j];
        }
        cout<<"\n";
    }
    cout<<sum<<endl;
    return 0;
}