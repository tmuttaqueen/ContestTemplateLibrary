#include<bits/stdc++.h>
using namespace std;


/// 0 _ based index
const int n = 1000000;
int parent[n];

void pre_process(int v)  ///make every node their own parent
{
    for( int i = 0; i < v; i++ )
        parent[i] = i;
}

/*
    if the tree is like this:
    4 -> 3 -> 8 -> 1
    after find_parent function
    4 -> 3
    4 -> 8
    4 -> 1
    and returns 4 as it the the parent of 1
*/
int find_parent( int x ) ///find the parent of a node
{
    if( x == parent[x] )  // base_case: the node is a parent to itself
        return x;
    return parent[x] = find_parent( parent[x] ); // go to the top of parent tree make the tree level smaller
}

/*  x = 4 and y = 5 is not in the same set

    2 -> 6 -> 3 -> 4
    8 -> 9 -> 12 -> 5
    after union function
    8 -> 9
    8 -> 12
    8 -> 5
    8 -> 2 -> 6
    8 -> 2 -> 3
    8 -> 2 -> 4
*/

void union_( int x, int y )  ///merge two set via an edge between x and y
{
    int px = find_parent( x ); // returns 2
    int py = find_parent( y ); // returns 8
    if( px != py )  // chack if the two set is connected by a edge
        parent[px] = py;  // merging the two set and node
    return;
}

int main()
{
    int v, e; // number of node, edge
    scanf("%d %d", &v, &e);
    pre_process(v);

    for( int i = 0; i < e; i++ )
    {
        int a, b;
        scanf("%d %d", &a, &b);
        union_(a,b);
    }
    for( int i = 0; i < v; i++ )
    {
        printf("parent of %d: %d\n", i, find_parent(i));
    }
    return 0;
}
