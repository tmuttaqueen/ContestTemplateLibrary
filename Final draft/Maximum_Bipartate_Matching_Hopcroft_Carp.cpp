#include<bits/stdc++.h>

using namespace std;

const int MAX = 100001, NIL = 0, INF = 1<<28;

struct BPM
{
    vector< int > edge[MAX];
    int n, m, match[MAX], dist[MAX];
// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// edge = NIL[0] ∪ edge1[edge[1---n]] ∪ edge2[edge[n+1---n+m]]

    bool bfs()
    {
        int u, v, len;
        queue< int > Q;
        for( int i = 1; i <= n; i++)
        {
            if( match[i] == NIL)
            {
                dist[i] = 0;
                Q.push(i);
            }
            else dist[i] = INF;
        }
        dist[NIL] = INF;
        while( !Q.empty() )
        {
            u = Q.front();
            Q.pop();
            if( u != NIL)
            {
                len = edge[u].size();
                for( int i = 0; i < len; i++ )
                {
                    v = edge[u][i];
                    if( dist[match[v]] == INF )
                    {
                        dist[match[v]] = dist[u] + 1;
                        Q.push(match[v]);
                    }
                }
            }
        }
        return dist[NIL] != INF;
    }

    bool dfs(int u)
    {
        int v, len;
        if( u != NIL)
        {
            len = edge[u].size();
            for( int i = 0; i < len; i++)
            {
                v = edge[u][i];
                if( dist[match[v]] == dist[u]+1 )
                {
                    if( dfs(match[v]) )
                    {
                        match[v] = u;
                        match[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }
    void init( int nn, int mm )
    {
        n = nn;
        m = mm;
        // match[] is assumed NIL for all vertex in edge. Clear it for multiple case.
        for( int i = 0; i <= n+m+2; i++ )
        {
            edge[i].clear();
            match[i] = 0;
            dist[i] = 0;
        }
    }
    //from set A to set B
    void addEdge( int u, int v )
    {
        //u := [1, n] ... v := [n+1,n+m]
        edge[u].push_back(v);
    }
    int hopcroft_karp()
    {
        int matching = 0, i;
        while( bfs() )
        {
            for( int i = 1; i <= n; i++)
                if( match[i] == NIL && dfs(i) )
                    matching++;
        }
        return matching;
    }

};

int main()
{

}
