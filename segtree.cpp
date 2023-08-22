#include <bits/stdc++.h>

using namespace std;
int x,y,n,q,st[100000],t,a[1000];

void build(int node,int ini,int fin)
{
    if (ini == fin) { 
        st[node] = a[ini];
        return;
    }
    int med = (ini+fin)/2;
    build(node*2+1,ini,med);
    build(node*2+2,med+1,fin);
    st[node] = st[node*2+1] + st[node*2+2]; //desired operation
    return;
}
int get(int node,int ini,int fin,int l,int r)
{
    if (l <= ini && fin <= r) return st[node]; //Fully in
    if (ini > r || fin < l) return 0; //Fully out
    int med = (ini+fin)/2;
    return get(node*2+1,ini,med,l,r) + get(node*2+2,med+1,fin,l,r); 
}
void upd(int node,int ini,int fin,int val,int pos)
{
    if (ini > pos || fin < pos) return; //Fully out
    if (ini == fin && ini == pos) { 
        st[node] = val;
        return;
    }
    int med = (ini+fin)/2;
    upd(node*2+1,ini,med,val,pos);  //Left sohn
    upd(node*2+2,med+1,fin,val,pos); //Right sohn
    st[node] = st[node*2+1] + st[node*2+2]; 
    return;
}
int main()
{
    cin>>n;
    for (int i=0;i<n;i++){
        cin>>a[i];
    }
    build(0,0,n-1);
    cin>>q;
    for (int i=0;i<q;i++) {
        cin>>t;
        if (t == 1){ ///Suma desde x hasta y.
            cin>>x>>y;
            cout<<get(0,0,n-1,x,y)<<"\n";
        }
        else if (t == 2){ ///Actualizar valor x, en la posicion y.
            cin >> x >> y;
            upd(0,0,n-1,x,y);
        }
    }
}
