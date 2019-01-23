#include <bits/stdc++.h>

using namespace std;

//necessary variables
const int mx = 1000;

void dfs( int u, vector< vector<int> >&edge, int is_vis[], int discovery_time[], int low[], int parent[], int &Time )
{
    int v, child = 0;
    is_vis[u] = 1;
    low[u] = discovery_time[u] = Time++;
    int l = edge[u].size();
    for( int i = 0; i < l; i++ )
    {
        v = edge[u][i];
        if( is_vis[v] == 0 )
        {
            if( parent[u] == -1 )
                child++;
            parent[v] = u;
            dfs(v, edge, is_vis, discovery_time, low, parent, Time );
            low[u] = min( low[u], low[v] );
            ///articulation points detection strat
            if( parent[u] == -1 && child > 1 )
                cout << u << " is an articulation point\n";
            if( parent[u] != -1 && low[v] >= discovery_time[u] )
                cout << u << " is an articulation point\n";
            ///detection finish
        }
        else if( v != parent[u] )
        {
            low[u] = min( low[u], discovery_time[v] );
        }
    }
    // u is articulation point if low[v] >= discovery_time[u] //O(E+V)
    // u-v is a bridge if low[v] > discovery_time[u] // O(E+V)
    // sort by finishing time is a dag ( higher to lower ) you will get topsort result //O(E+Vlogn)
}

void articulation( int vertex, int edg )
{
    int discovery_time[mx], is_vis[mx], low[mx], parent[mx];
    int Time = 1;
    memset( is_vis, 0, sizeof(is_vis) );
    memset( parent, -1, sizeof(parent) );
    for( int i = 1; i <= vertex; i++ )
    {
        if( is_vis[i] == 0 )
        {
            dfs(i, edge, is_vis, discovery_time, low, parent, Time );
            parent[i] = -1;
        }
    }
}



