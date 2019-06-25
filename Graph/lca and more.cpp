#include <bits/stdc++.h>
using namespace std;

const int SZ = 1000005, mod = 1000000007;
const int nver = 100005, factor = 20;
int par[nver], depth[nver], lca[factor][nver];
vector<int>edge[nver];
//create the lca of a node
void create_lca( int lca[][nver], int par[], int v ) // v is vertex number
{
    lca[0][v] = par[v];
    for( int j = 1; j < factor; j++ )
    {
        if( lca[j-1][v] != -1 )
            lca[j][v] = lca[j-1][ lca[j-1][v] ];
        else
            break;
    }
}
//find nth parent of a node
int nthpar( int lca[][nver], int v, int n )
{
    for( int i = factor - 1; i >= 0 && n > 0; i-- )
    {
        if( (1<<i) <= n )
        {
            v = lca[i][v];
            n -= (1<<i);
        }
    }
    return v;
}
//find lca of two nodes u and v
int find_lca( int lca[][nver], int depth[], int u, int v )
{
    if( depth[u] < depth[v] ) //after this u is deeper than v
    {
        swap(u,v);
    }
    int diff = depth[u] - depth[v];
    u = nthpar(lca, u, diff);
    if( u == v )
        return u;
    for( int i = factor-1; i >= 0; i--  )
    {
        if( lca[i][u] != lca[i][v] )
        {
            u = lca[i][u];
            v = lca[i][v];
        }
    }
    return lca[0][u];
}
//dfs for parent and depth
void dfs( int u, int p )
{
    for( int v: edge[u] )
    {
        if( v != p )
        {
            par[v] = u;
            depth[v] = depth[u] + 1;
            create_lca( lca, par, v );
            dfs(v,u);
        }
    }
}




