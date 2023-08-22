#include <bits/stdc++.h>

using namespace std;

bool criba[1000005];
int n;

int main()
{
    criba[1] = true;
    for (int i = 1; i<=100000; i++){
        if (!criba[i]){
            for (int j = 2; i*j<=100000; j++){
                criba[i*j] = true;
            }
        }
    }
    cin>>n;
    for (int x = 1; x<=n; x++){
        if (!criba[x]){
            cout<<x<<"\n";
        }
    }
}
