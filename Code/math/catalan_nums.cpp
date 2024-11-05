#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define nl '\n'
#define fast cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false)
#define fore(i,a,b) for(int i=a;i<b;++i)

using namespace std;

const ll mod = 1e9+7;
const ll maxn = 1e5+5;
int catalan[maxn+5];
void init() {
    catalan[0] = catalan[1] = 1;
    for (int i=2; i<=maxn; i++) {
        catalan[i] = 0;
        for (int j=0; j < i; j++) {
            catalan[i] += (catalan[j] * catalan[i-j-1]) % mod;
            if (catalan[i] >= mod) {
                catalan[i] -= mod;
            }
        }
    }
}
/*
Formula to get the nth catalan: C_n = (1/(n+1))*nck(2*n,n)
Applications of Catalan Numbers, where Cn is:
    > Number of correct bracket sequence consisting of 'n'  opening and  'n'  closing brackets.
    > The number of rooted full binary trees with  'n + 1'  leaves (vertices are not numbered). 
      A rooted binary tree is full if every vertex has either two children or no children
    > The number of ways to completely parenthesize 'n + 1'  factors.
    > The number of triangulations of a convex polygon with  'n + 2'  sides (i.e. the number of 
      partitions of polygon into disjoint triangles by using the diagonals).
    > The number of ways to connect the '2n'  points on a circle to form  'n'  disjoint chords.
    > The number of non-isomorphic full binary trees with  'n'  internal nodes (i.e. nodes 
      having at least one son).
    > The number of monotonic lattice paths from point (0, 0) to point (n, n) in a square lattice 
      of size  'n' x 'n' , which do not pass above the main diagonal (i.e. connecting  '(0, 0)'  to  
     '(n, n)')
    > Number of permutations of length 'n'  that can be stack sorted (i.e. it can be shown that the 
      rearrangement is stack sorted if and only if there is no such index  i < j < k, such that  
      a_k < a_i < a_j  ).
    > The number of non-crossing partitions of a set of  'n'  elements.
    > The number of ways to cover the ladder 1...n using  'n'  rectangles (The ladder consists of  
      'n'  columns, where  i-th  column has a height i ).
*/