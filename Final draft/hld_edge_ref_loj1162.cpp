
namespace HLD
{
const int LOG = 18, MAX = 100005;
int lca[LOG][MAX];
int dist[MAX], par[MAX], depth[MAX];
int n, root;
vector<int>edge[MAX];
int chain, cur;
int sz[MAX], //size of subtree of 'u'
    chainNo[MAX], //In what chain is the vertex 'u' in
    chainLen[MAX], //Length of a 'chain'
    posChain[MAX], //position of 'u' in a chain-1 based
    chainHead[MAX], //Head of a 'chain'
    ind[MAX]; //position of vertex 'u' in mapped hld array

///call it everytime for initializing the HLD process before adding edge
void init( int v, int r = 1 )
{
    n = v;
    root = r;
    dist[root] = 0;
    depth[root] = 0;
    chain = 1;
    cur = 1;
    for( int i = 1; i <= n; i++ )
    {
        chainLen[i] = 0;
        edge[i].clear();
    }
}

/************** ESSENTIAL PART OF HLD START ****************/

void addEdge( int a, int b )
{
    edge[a].push_back(b);
    edge[b].push_back(a);
}

void dfs( int u, int p )
{
    sz[u] = 1;
    if( p != -1 )
    {
        dist[u] = dist[p] + 1; //if needed change weight
        depth[u] = depth[p] + 1;
    }
    par[u] = p;
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( p != v )
        {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

/************** ESSENTIAL PART OF HLD END ****************/

/************** LCA PART OF HLD START ********************/

///1st step of HLD call it first
void create_lca()
{
    dfs(1, -1);
    for( int i = 1; i <= n; i++ )
        lca[0][i] = par[i];
    for( int p = 1; p < LOG; p++ )
    {
        for( int v = 1; v <= n; v++ )
        {
            if( lca[p-1][v] != -1 )
                lca[p][v] = lca[p-1][ lca[p-1][v] ];
            else
                lca[p][v] = -1;
        }
    }
}

///return the child below the LCA in
///order by passing the nodes to function
pair<int,int> find_lca( int a, int b ) /// u, v
{
    int f = 0;
    if( depth[a] < depth[b] )
    {
        f = 1;
        swap(a,b);
    }
    int d = depth[a] - depth[b], c = 0;
    int temp = d, v = a;
    while( d > 0 )
    {
        if( d&1 )
            a = lca[c][a];
        d >>= 1;
        c++;
    }
    if( a == b)
    {
        a = v;
        d = temp-1;
        c = 0;
        while( d > 0 )
        {
            if( d&1 )
                a = lca[c][a];
            d >>= 1;
            c++;
        }
        //-1 indicates that b is an ancestor of a
        //for vertex HLD use path (u, par[xx] ), u is highest depth vertex
        //for edge HLD use path (u, xx), u is highest depth vertex
        return mp(a, -1);
    }
    for( int i = LOG-1; i >= 0; i--  )
    {
        if( lca[i][par[a]] != lca[i][par[b]] )
        {
            a = lca[i][a];
            b = lca[i][b];
        }
    }
    //for vertex HLD use path (u, par[xx] ), (v, par[v])
    //for edge HLD use path(u, xx), (v, yy)
    if( par[a] != par[b] )
    {
        if(f) return mp( par[b], par[a] );
        else return mp( par[a], par[b] );
    }
    if( f ) return mp(b,a);
    else return mp(a,b);
}

/************** LCA PART OF HLD END ****************/

/************** CREATING HLD **********************/
///2nd step of HLD call it second
void create_hld( int u )
{
    ind[u] = cur++;
    chainNo[u] = chain;
    chainLen[chain]++; //memset it for multiple test case
    posChain[u] = chainLen[chain];
    int maxSize = -1, maxV = -1;
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( v == par[u] ) continue;
        if( maxSize < sz[v] )
        {
            maxV = v;
            maxSize = sz[v];
        }
    }
    if( maxV != -1 )
        create_hld( maxV );
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( v == par[u] || v == maxV ) continue;
        chain++;
        chainHead[chain] = v;
        create_hld(v);
    }
}

/***************** HLD CREATION END *******************/


/************** SEGMENT TREE START *******************/
int data[MAX]; // value of mapped vertex
pii tree[4*MAX];

void init_tree( int cn, int s, int e )
{
    if( s == e )
    {
        tree[cn] = mp(data[s], data[s]) ;
        return;
    }
    int m = (s+e)/2;
    init_tree( cn<<1, s, m );
    init_tree( (cn<<1)+1, m+1, e );
    tree[cn] = mp( max(tree[cn<<1].xx,tree[ (cn<<1)+1 ].xx), min(tree[cn<<1].yy, tree[ (cn<<1)+1 ].yy) );
}

/*void update_tree( int cn, int s, int e, int x, int v )
{
    //if( x < s || e < x ) return;
    if( x == s && x == e )
    {
        tree[cn] = v;
        return;
    }
    int m = (s+e)/2;
    if( x <= m )
        update_tree( cn<<1, s, m, x, v );
    else
        update_tree( (cn<<1)+1, m+1, e, x, v );
    tree[cn] = tree[cn<<1] + tree[ (cn<<1)+1 ];
    return;
}*/

pii query_tree( int cn, int s, int e, int x, int y )
{
    if( y < s || x > e ) return mp( -1, INT_MAX );
    if( s >= x && e <= y )
    {
        return tree[cn];
    }
    int m = (s+e)/2;
    pii a = mp(-1, INT_MAX),  b = mp(-1, INT_MAX);
    if( !(y < s || x > m) )
        a = query_tree( cn<<1, s, m, x, y );
    if( !(y < (m+1) || x > e) )
        b = query_tree( (cn<<1)+1, m+1, e, x, y );
    return mp( max( a.xx, b.xx ), min( a.yy, b.yy ) );
}

/**************** SEGMENT TREE END ******************/

/**************** QUERY AND UPDATE START ************/

pii query_up( int x, int p )
{
    pii ans = mp(-1, INT_MAX);
    while(1)
    {
        if( chainNo[x] == chainNo[p] )
        {
            pii d = query_tree( 1, 1, n, ind[p], ind[x] );
            ans = mp( max(ans.xx, d.xx), min( ans.yy, d.yy ) );
            break;
        }
        int l = ind[x] - posChain[x] + 1, r = ind[x];
        pii d = query_tree( 1, 1, n, l, r );
        ans = mp( max(ans.xx, d.xx), min( ans.yy, d.yy ) );
        x = par[chainHead[ chainNo[x] ]];
    }
    return ans;
}


pii query( int x, int y )
{

    pii p = HLD::find_lca(x, y);
    if( p.yy == -1 )
    {
        if( depth[x] < depth[y] ) x = y;
        return query_up( x, p.xx );
    }
    else
    {
        pii a = query_up( x, p.xx );
        pii b = query_up( y, p.yy );
        return mp( max(a.xx, b.xx), min( a.yy, b.yy ) );
    }
}
/*************************** QUERY AND UPDATE END ********************/
}

const int MAX = 100005;

vector<int> weight[MAX], edge[MAX];

int main()
{
    int t, caseno = 1;
    cin >> t;
    while(t--)
    {
        int a, b, n, w;
        //cin >> n;
        scanf("%d", &n);
        HLD::init( n );
        for( int i = 1; i <= n; i++ )
        {
            edge[i].clear();
            weight[i].clear();
        }
        for( int i = 1; i < n; i++ )
        {
            //cin >> a >> b >> w;
            scanf("%d %d %d", &a, &b, &w);
            edge[a].pb(b);
            weight[a].pb(w);
            edge[b].pb(a);
            weight[b].pb(w);
            HLD::addEdge( a, b );
        }

        HLD::create_lca();
        HLD::create_hld(1);
        for( int i = 1; i <= n; i++ )
        {
            for( int j = 0; j < edge[i].size(); j++ )
            {
                if( HLD::par[ edge[i][j] ] == i )
                {
                    int d = HLD::ind[ edge[i][j] ];
                    HLD::data[d] = weight[i][j];
                }
            }
        }
        HLD::init_tree(1, 1, n);
        int q;
        //cin >> q;
        scanf("%d", &q);
        printf("Case %d:\n", caseno++);
        while(q--)
        {
            int a, b;
            //cin >> a >> b;
            scanf("%d %d", &a, &b);
            pii p = HLD::query( a, b );
            printf("%d %d\n", p.yy, p.xx );
        }

    }


    return 0;
}
