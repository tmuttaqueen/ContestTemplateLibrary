///******************* BRIDGE TREE - Kill Brigdes ********************
#include <bits/stdc++.h>
using namespace std;
const int M = 200005;

int U[M], V[M], Time, dis[M], compNo[M], compCount;
bool isBridge[M];
vector<int>edge[M]; //adjacent edge with vertex u
vector<int>tree[M]; //adjacency list of bridge tree 1 based

inline int adj( int u, int e )
{
    return u == U[e]? V[e]: U[e];
}

void dfsBridge( int u, int e )
{
    dis[u] = Time++;
    int low = dis[u];
    for( int x: edge[u] )
    {
        if( x == e ) continue;
        int v = adj(u, x);
        if( dis[v] == 0 )
        {
            dfsBridge(v, x);
        }
        low = min( low, dis[v] );
    }
    if( low >= dis[u] && e != -1) isBridge[e] = 1;
    dis[u] = low;
}
//dfa construct tree
void dfsCTree(int u)
{
    int curcomp = compCount;
    compNo[u] = curcomp;
    queue<int>qq;
    qq.push(u);
    while( !qq.empty() )
    {
        int t = qq.front();
        qq.pop();
        for( int x: edge[t] )
        {
            int v = adj(t, x);
            if( compNo[v] ) continue;
            if( isBridge[x] == 1 )
            {
                compCount++;
                tree[curcomp].pb(compCount);
                tree[compCount].pb(curcomp);
                dfsCTree(v);
            }
            else
            {
                compNo[v] = curcomp;
                qq.push(v);
            }
        }
    }

}

void bridge_tree()
{
    Time = 1;
    compCount = 1;
    memset( compNo, 0, sizeof compNo );
    memset( dis, 0, sizeof dis );
    memset( isBridge, 0, sizeof isBridge );
    dfsBridge(1, -1);
    dfsCTree(1);
}

int par[M], dist[M];
void dfsDist( int u, int p )
{
    par[u] = p;
    for( int v : tree[u] )
    {
        if( v == p ) continue;
        dist[v] = dist[u] + 1;
        dfsDist(v, u);
    }
}

vector<int>val;
int h[M];

void dfsHeight( int u, int p )
{
    h[u] = 0;
    for( int v: tree[u] )
    {
        if( v == p ) continue;
        dfsHeight(v, u);
        h[u] = max( h[u], h[v] + 1 );
    }
}

void dfsSolve(int u, int p, int len)
{
    int f = 1, leaf = 1;
    for( int v: tree[u] )
    {
        if( v == p ) continue;
        leaf = 0;
        if( f == 1 && h[u] == h[v] + 1 )
        {
            f = 0;
            dfsSolve(v, u, len+1);
        }
        else
        {
            dfsSolve(v, u, 1);
        }
    }
    if(leaf) val.push_back(len);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    //filein;
    int n, m, q, a, b;
    cin >> n >> m >> q;
    for( int i = 1; i <= m; i++ )
    {
        cin >> a >> b;
        U[i] = a;
        V[i] = b;
        edge[a].pb(i);
        edge[b].pb(i);
    }
    bridge_tree();
    dist[1] = 0;
    dfsDist(1,-1);
    int d = 0, v = -1;
    for( int i = 1; i <= compCount; i++ )
    {
        if( dist[i] > d )
        {
            v = i;
            d = dist[i];
        }
    }
    dist[v] = 0;
    dfsDist(v,-1);
    d = 0;
    int u = -1;
    for( int i = 1; i <= compCount; i++ )
    {
        if( dist[i] > d )
        {
            u = i;
            d = dist[i];
        }
    }
    while( dist[u]*2 > d )
    {
        u = par[u];
    }
    //cout << u << endl;
    dfsHeight(u, -1);
    dfsSolve(u, -1, 0);
    sort( val.begin(), val.end() );
    reverse( val.begin(), val.end() );
    for( int i = 1; i < val.size(); i++ )
        val[i] += val[i-1];
    while(q--)
    {
        int k;
        cin >> k;
        int ans = 0;
        int m = min( 2*k, (int)val.size() );
        ans = val[m-1];
        cout << ans << "\n";
    }
    return 0;
}
