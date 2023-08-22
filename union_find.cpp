#include <iostream>

using namespace std;

int N;

struct UnionFind{
    int dad;
    int ran;
    int tam;
};

UnionFind uf[10005];

int bus(int u){
    if (uf[u].dad != u) uf[u].dad = bus(uf[u].dad);
    return uf[u].dad;
}

bool igual (int a, int b){
    a = bus(a);
    b = bus(b);
    if (a == b) return 1;
    else return 0;
}

bool agregar (int a, int b){
    a = bus(a);
    b = bus(b);
    if (a != b){
        if (uf[a].ran > uf[b].ran){
            uf[b].dad = a;
            uf[b].tam += uf[a].tam;
        }
        else if (uf[a].ran > uf[a].ran){
            uf[a].dad = b;
            uf[a].tam += uf[b].tam;
        }
        else{
            uf[b].dad = a;
            uf[a].ran++;
            uf[a].tam += uf[b].tam;
        }
    }
}

int main()
{
    cin>>N;
    for (int i = 0; i<N; i++){
        uf[i].dad = i;
        uf[i].ran = 0;
        uf[i].tam = 1;
    }
}
