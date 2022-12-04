#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class T, class Comp = std::less<T>>
using indexed_set = tree<T, null_type, Comp, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V, class Comp = std::less<K>>
using indexed_map = tree<K, V, Comp, rb_tree_tag, tree_order_statistics_node_update>;