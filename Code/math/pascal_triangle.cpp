#include <iostream>
#define ll long long

using namespace std;

ll C[32][32];

void pascal(){
    const int maxn = 10;
    C[0][0] = 1;
    for (int i = 1; i<=maxn; i++){
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j<i; j++){
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}

int main()
{
    pascal();
}
