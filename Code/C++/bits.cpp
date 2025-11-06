mask |= (1<<n) // prender bit-N
mask ^= (1<<n) // flippear bit-N
mask &= ~(1<<n) // apagar bit-N
if(mask&(1<<n)) // checkar bit-n
T = ((mask)&(-mask)) // LSO
__builtin_ffs(mask); // indice del LSO (indexado en 1)
//  Iterate over the subsets of S.
for(int subset= S; subset; subset= (subset-1) & S)
  for (int subset=0;subset=subset-S&S;) // Increasing order

// Bitset basics (reduces speed up by a dividing factor of 64):
bitset<1000> b;      // 1000 bits, all 0
b[5] = 1;            // set bit 5
b.set(10);           // also set bit 10
b.reset(5);          // clear bit 5
b.flip(7);           // toggle bit 7
b.any();             // true if any bit = 1
b.none();            // true if all bits = 0
b.count();           // number of bits set to 1
b.to_ulong();        // convert to unsigned long
b.to_string();       // get a string like "0010110"

// Bitset fast set operations
bitset<1000> A, B;
bitset<1000> C = A & B;  // intersection
bitset<1000> D = A | B;  // union
bitset<1000> E = A ^ B;  // symmetric difference

// Bitset comparison tricks:
if ((A & B) == B) { /* B is subset of A */ }
if ((A & B).any()) { /* intersection non-empty */ }

