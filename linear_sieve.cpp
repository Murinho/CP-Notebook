#include <bits/stdc++.h>

using namespace std;

int main()
{
    const int N = 10000000;
    vector<int> lp(N+1);
    vector<int> pr;
    int a;

    for (int i=2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j=0; j < (int)pr.size() && pr[j] <= lp[i] && i*pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
        }
    }
    for (int i = 0; i<10; i++) cout<<pr[i]<<" ";
}
