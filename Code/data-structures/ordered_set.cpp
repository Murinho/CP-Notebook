#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int,null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;

ordered_multiset omst;
//find_by_order(k): finds the element that is the Kth in the set.
//order_of_key(k): finds the number of elements strictly smaller than k (or {k,pos} if multiset).

ll get_kth_element(ll k){ return (*omst.find_by_order(k)).fst;} // 0-indexed.

ll get_elements_less_than_k(ll k, ll pos){ return (omst.order_of_key({k, pos}));}

void insert(ll val, ll pos){ omst.insert({val,pos}); }

void erase(ll val, ll pos){ omst.erase(omst.find_by_order(omst.order_of_key({val,pos})));}