#include <bits/stdc++.h>

using namespace std;

void counting_sort(vector <int> &p, vector <int> &c){
    int tam = p.size();
    vector <int> cont(tam);
    for (auto x: c){
        cont[x]++;
    }
    vector <int> p_new(tam);
    vector <int> pos(tam);
    pos[0] = 0;
    for (int i = 1; i<tam; i++){
        pos[i] = pos[i-1] + cont[i-1];
    }
    for (auto x: p){
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}

int main()
{
    string s;
    cin>>s;
    s += "$";
    int tam = s.size();
    vector <int> p(tam), c(tam);
    {
        vector < pair <char, int> > a(tam);
        for (int i = 0; i<tam; i++) a[i] = {s[i], i};
        sort(a.begin(),a.end());

        for (int i = 0; i<tam; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i<tam; i++){
            if (a[i].first == a[i-1].first){
                c[p[i]] = c[p[i-1]];
            }
            else{
                c[p[i]] = c[p[i-1]] + 1;
            }
        }
    }

    int k = 0;
    while ((1 << k) < tam){

        for (int i = 0; i<tam; i++){
            p[i] = (p[i] - (1 << k) + tam) %tam;
        }
        //Radix sort:
        counting_sort(p,c);
        vector <int> c_new(tam);
        c_new[p[0]] = 0;
        for (int i = 1; i<tam; i++){
            pair <int, int> prev = {c[p[i-1]],c[(p[i-1] + (1 << k)) %tam]};
            pair <int, int> now = {c[p[i]], c[(p[i] + (1 << k)) %tam]};
            if (now == prev){
                c_new[p[i]] = c[p[i-1]];
            }
            else{
                c_new[p[i]] = c[p[i-1]] + 1;
            }
        }

        k++;
    }
    for (int i = 1; i<tam; i++){
        cout << p[i] <<" ";
    }
    return 0;
}
