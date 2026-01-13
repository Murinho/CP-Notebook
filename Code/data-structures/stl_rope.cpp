#include <ext/rope>
using namespace __gnu_cxx;
rope<int> s;
/*
1. Construction:
rope<char> r1;
rope<char> r2("hello");
rope<char> r3 = r2;

2. Concatenation O(log n)
rope<char> a("hello");
rope<char> b("world");

rope<char> c = a + b;
a += b;

3. Indexing (Read/Write) O(log n)
char x = r[5];
r[0] = 'H';

4. Substring/Split O(log n)
rope<char> sub = r.substr(pos, len);
- Doesn't copy characters, just reuses tree nodes

5. Insert O(log n)
r.insert(pos, "ABC") or r.insert(pos, other_rope)

6. Erase O(log n)
r.erase(pos, len)

7. Replace (Erase + Insert)
r.replace(pos, len, "XYZ");
*/