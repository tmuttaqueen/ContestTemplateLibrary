///************DINIC EDGE LIST***************

#include<bits/stdc++.h>

using namespace std;

struct Dinic
{
    struct edge
    {
        int ind, to, cap;
        bool isReal;
    };
    int s, t, V;
    vector<int> level;
    vector<bool>flag;
    vector<vector<edge>> all;


    Dinic(int v = 10005)
    {
        this->V = v;
        flag.resize(V, 0);
        level.resize(V, 0);
        all.resize(V);
        for( int i = 0; i < V; i++ )
            all[i].clear();
    }
    void setGraph( int s, int t )  //source, destination
    {
        this->s = s;
        this->t = t;
    }
    void addEdge( int u, int v, int c) //from, to, capacity
    {
        all[u].push_back( { all[v].size() , v, c, true} );
        all[v].push_back( { all[u].size()-1 , u, 0, false} );
    }

    bool bfs( int u ) //source
    {
        level[u] = 0;
        queue<int>q;
        flag.clear();
        flag.resize(V, 0);
        flag[u] = 1;
        q.push(u);
        while( !q.empty() )
        {
            int u = q.front(); q.pop();
            for( int i = 0; i < all[u].size(); i++ )
            {
                int v = all[u][i].to, c = all[u][i].cap;
                if( c > 0 && flag[v] == 0 )
                {
                    flag[v] = 1;
                    level[v] = level[u]+1;
                    q.push(v);
                }
            }
        }
        return flag[t]; //is possible to go destination?
    }
    int augmentPath( int u, int f ) //node, flow so far
    {
        if( u == t ) return f;
        int tot = 0;
        for( int i = 0; i < all[u].size(); i++ )
        {
            int v = all[u][i].to, ind = all[u][i].ind, c = all[u][i].cap;
            if( level[v] == level[u]+1 && c > 0 )
            {
                int d = augmentPath( v, min( f, c ) );
                all[u][i].cap -= d;
                all[v][ind].cap += d;
                tot += d;
                f -= d;
                if( f <= 0 )
                    break;
            }
        }
        return tot;
    }

    int maxFlow()
    {
        int flow = 0;
        while( bfs( s ) )
        {
            flow += augmentPath(s, 2000000);
        }
        //to get mincut check flag here
        //to get flow per edge check capacity here
        return flow;
    }
};


int main()
{
    int n, m;
    cin >> n >> m;
    Dinic flow(n+5);
    for( int i = 0; i < m; i++ )
    {
        int a, b, c;
        cin >> a >> b >> c;
        flow.addEdge(a,b,c);
    }
    flow.setGraph(1,n);
    cout <<  flow.maxFlow() << endl;
    return 0;
}

///**************HOPCROFT CARP**********************

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


///***************HUNGARIAN ALGORITHM******************
#include <bits/stdc++.h>

using namespace std;

const int MAX = 105;

/// n = number of row and m = number of columns in 1 based, flag = 1-MAXIMIZE or 0-MINIMIZE
/// match[i] contains the column to which row i is matched
/// set mat[i][j] to inf if i and j is not connected
template<typename T>
struct WBM
{
    bool visited[MAX];
    int  P[MAX], way[MAX], match[MAX];
    T minv[MAX], ar[MAX][MAX], U[MAX], V[MAX];

    T hungarian(int n, int m, T mat[MAX][MAX], int flag = 0)
    {
        memset(U, 0, sizeof(U));
        memset(V, 0, sizeof(V));
        memset(P, 0, sizeof(P));
        memset(ar, 0, sizeof(ar));
        memset(way, 0, sizeof(way));
        T inf = 1e18;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                ar[i][j] = mat[i][j];
                if (flag) ar[i][j] = -ar[i][j];
            }
        }
        if (n > m) m = n;

        int i, j, a, b, c, d;
        T r, w;
        for (i = 1; i <= n; i++)
        {
            P[0] = i, b = 0;
            for (j = 0; j <= m; j++) minv[j] = inf, visited[j] = false;

            do
            {
                visited[b] = true;
                a = P[b], d = 0, w = inf;

                for (j = 1; j <= m; j++)
                {
                    if (!visited[j])
                    {
                        r = ar[a][j] - U[a] - V[j];
                        if (r < minv[j]) minv[j] = r, way[j] = b;
                        if (minv[j] < w) w = minv[j], d = j;
                    }
                }

                for (j = 0; j <= m; j++)
                {
                    if (visited[j]) U[P[j]] += w, V[j] -= w;
                    else minv[j] -= w;
                }
                b = d;
            }
            while (P[b] != 0);

            do
            {
                d = way[b];
                P[b] = P[d], b = d;
            }
            while (b != 0);
        }
        for (j = 1; j <= m; j++) match[P[j]] = j;

        return (!flag) ? -V[0] : V[0];
    }
};


int ara[MAX][MAX];

int main()
{
    WBM<int> wm;
    int n = 3, m = 4;
    for( int i = 1; i <= n; i++ )
    {
        ara[i][i+1] = 1;
        int f = 2;
        for( int j = 1; j <= m; j++ )
        {
            if( j == i+1 ) continue;
            ara[i][j] = f++;
        }
    }
    cout << wm.hungarian(n, m, ara) << endl;
    for( int i = 1; i <= n; i++ )
        cout << wm.match[i] << endl;

    return 0;
}

///***************** MINCOST MAXFLOW****************************

using namespace std;

/// Min-cost Max-flow using SPFA (Shortest Path Faster Algorithm)
/// 0 Based indexed for directed weighted graphs (for undirected graphs, just add two directed edges)

namespace mcmf
{
const int MAX = 1000010;
const long long INF = 1LL << 60;

long long cap[MAX], flow[MAX], cost[MAX], dis[MAX];
int n, m, s, t, Q[MAX*10], adj[MAX], link[MAX], last[MAX], from[MAX], visited[MAX];

void init(int nodes, int source, int sink)
{
    m = 0, n = nodes, s = source, t = sink;
    for (int i = 0; i <= n; i++) last[i] = -1;
}

void addEdge(int u, int v, long long c, long long w)
{
    adj[m] = v, cap[m] = c, flow[m] = 0, cost[m] = +w, link[m] = last[u], last[u] = m++;
    adj[m] = u, cap[m] = 0, flow[m] = 0, cost[m] = -w, link[m] = last[v], last[v] = m++;
}

bool spfa()
{
    int i, j, x, f = 0, l = 0;
    for (i = 0; i <= n; i++) visited[i] = 0, dis[i] = INF;

    dis[s] = 0, Q[l++] = s;
    while (f < l)
    {
        i = Q[f++];
        for (j = last[i]; j != -1; j = link[j])
        {
            if (flow[j] < cap[j])
            {
                x = adj[j];
                if (dis[x] > dis[i] + cost[j])
                {
                    dis[x] = dis[i] + cost[j], from[x] = j;
                    if (!visited[x])
                    {
                        visited[x] = 1;
                        if (f && rand() & 7) Q[--f] = x;
                        else Q[l++] = x;
                    }
                }
            }
        }
        visited[i] = 0;
    }
    return (dis[t] != INF);
}

pair <long long, long long> solve()
{
    int i, j;
    long long mincost = 0, maxflow = 0;

    while (spfa())
    {
        long long aug = INF;
        for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i])
        {
            aug = min(aug, cap[j] - flow[j]);
        }
        for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i])
        {
            flow[j] += aug, flow[j ^ 1] -= aug;
        }
        maxflow += aug, mincost += aug * dis[t];
    }
    return make_pair(mincost, maxflow);
}
}
