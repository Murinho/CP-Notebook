#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b)
            swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}

int lcm(int a, int b){
    return a / gcd(a,b) * b;
}

int main()
{
    int a,b;
    cin>>a>>b;
    cout<<gcd(a,b)<<endl;
    cout<<lcm(a,b)<<endl;
}
