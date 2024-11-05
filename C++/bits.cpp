mask |= (1<<n) // prender bit-N
mask ^= (1<<n) // flippear bit-N
mask &= ~(1<<n) // apagar bit-N
if(mask&(1<<n)) // checkar bit-n
T = ((mask)&(-mask)) // LSO
__builtin_ffs(mask); // indice del LSO (indexado en 1)
//  Iterate over the subsets of S.
for(int subset= S; subset; subset= (subset-1) & S)
    for (int subset=0;subset=subset-S&S;) // Increasing order