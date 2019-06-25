#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

template<
	  typename Key, // Key type
	  typename Mapped, // Mapped-policy
	  typename Cmp_Fn = std::less<Key>, // Key comparison functor
	  typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
	  template<
	  typename Const_Node_Iterator,
	  typename Node_Iterator,
	  typename Cmp_Fn_,
	  typename Allocator_>
	  class Node_Update = null_node_update, // A policy for updating node invariants
	  typename Allocator = std::allocator<char> > // An allocator type
class tree;

typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update>
ordered_set;

int main()
{

    ordered_set os;
    os.insert(1);
    os.insert(43);
    os.insert(1);
    os.insert(2);
    os.insert(3);
    os.insert(4);



    return 0;
}
