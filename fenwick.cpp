#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define lsb(x) ((x)&(-x))

using namespace std;

const int maxn = 1e5+5;
int arr[maxn];

void add(int x, int v){
    while (x <= maxn-5){
        arr[x] += v;
        x += lsb(x);
    }
}
int get(int x){
    int freq = 0;
    while (x > 0){
        freq += arr[x];
        x -= lsb(x);
    }
    return freq;
}

int main()
{
    int pos,val,n,k,q,a,b,ans;
    cin>>n>>k;
    for (int i = 0; i<n; i++){
        arr[i] = 0;
    }
    for (int i = 0; i<k; i++){
        cin>>q;
        if (q == 1){
            ///Add.
            cin>>pos>>val;
            add(pos,val);
        }
        else if (q == 2){
            ///Get:
            cin>>a>>b;
            ans = get(b) - get(a-1);
            cout<<ans<<endl;
        }
    }
}
