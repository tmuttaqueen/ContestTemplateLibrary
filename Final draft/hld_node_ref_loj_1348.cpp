
const int M = 34567;

vector<int>edge[M];

/************************** LCA START **************************/
class LCA
{
    int factor;
    int **lca;
    int *dist;
    int n, root;
public:
    LCA() {}
    void setLCA( int vertex, int root = 1 )
    {
        n = vertex;
        this->root = root;
        factor = 16;
        lca = new int*[factor+1];
        for( int i = 0; i <= factor; i++ )
            lca[i] = new int[n+5];
        dist = new int[n+5];
    }
    //par is the parent array we get from traversing the tree
    //d is the distance array to all vertex from root
    void create( int *par, int *d = 0 ) //creates binary power parent of tree
    {
        for( int i = 1; i <= n; i++ )
        {
            if( d != 0 )
            {
                dist[i] = d[i];
            }
            else
                dist[i] = -1;
        }
        par[root] = -1;
        for( int i = 0; i <= n; i++ )
            lca[0][i] = par[i];
        for( int j = 1; j <= factor; j++ )
        {
            for( int i = 1; i <= n; i++ )
            {
                if( lca[j-1][i] != -1 )
                    lca[j][i] = lca[j-1][ lca[j-1][i] ];
                else
                    lca[j][i] = -1;
            }
        }
    }
    //finds lca of vertex u and v
    int find_lca( int u, int v )
    {
        if( dist[u] < dist[v] )
            swap(u,v); //after this u is deeper than v
        int diff = dist[u] - dist[v];
        int c = 0;
        while( diff > 0 )
        {
            if( diff&1 )
                u = lca[c][u];
            diff >>= 1;
            c++;
        }
        if( v == u) return v;
        for( int i = factor; i >= 0; i--  )
        {
            if( lca[i][u] != lca[i][v] )
            {
                u = lca[i][u];
                v = lca[i][v];
            }
        }
        return lca[0][u];
    }
    //find distance between u and v
    int distance( int u, int v )
    {
        if( u < 1 || v < 1 || u > n || v > n )
            return 0; //modify return value as needed
        int l = find_lca(u, v);
        return dist[u] + dist[v] - 2*dist[l];
    }
    ~LCA()
    {
        for( int i = 0; i <= factor; i++ ) delete[] lca[i];
        delete[] lca;
        delete[] dist;
    }
};

/************************** LCA END ***************************/

/************************* HLD PART START *********************/

int level[M],
    sz[M], //size of subtree of 'u'
    parent[M], //parent of vertex 'u'
    chainNo[M], //In what chain is the vertex 'u' in
    chainLen[M], //Length of a 'chain'
    posChain[M], //position of 'u' in a chain-1 based
    chainHead[M], //Head of a 'chain'
    Index[M]; //position of vertex 'u' in mapped array

void dfs( int u, int p )
{
    sz[u] = 1;
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( v != p )
        {
            level[v] = level[u] + 1;
            parent[v] = u;
            dfs(v,u);
            sz[u] += sz[v];
        }
    }
}

int chain, cur;

void create_hld( int u )
{
    Index[u] = cur++;
    chainNo[u] = chain;
    chainLen[chain]++; //memset it for multiple test case
    posChain[u] = chainLen[chain];
    int maxSize = -1, maxV = -1;
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( v == parent[u] ) continue;
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
        if( v == parent[u] || v == maxV ) continue;
        chain++;
        chainHead[chain] = v;
        create_hld(v);
    }
}

/************************* HLD PART END *********************/

/*************************** SEGMENT TREE START ***************************/
int data[M]; // value of mapped vertex
int tree[4*M];

void init_tree( int cn, int s, int e )
{
    if( s == e )
    {
        tree[cn] = data[s];
        return;
    }
    int m = (s+e)/2;
    init_tree( cn<<1, s, m );
    init_tree( (cn<<1)+1, m+1, e );
    tree[cn] = tree[cn<<1] + tree[ (cn<<1)+1 ];
}

void update_tree( int cn, int s, int e, int x, int v )
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
}

int query_tree( int cn, int s, int e, int x, int y )
{
    if( y < s || x > e ) return 0;
    if( s >= x && e <= y )
    {
        return tree[cn];
    }
    int m = (s+e)/2, a = 0,  b = 0;
    if( !(y < s || x > m) )
        a = query_tree( cn<<1, s, m, x, y );
    if( !(y < (m+1) || x > e) )
        b = query_tree( (cn<<1)+1, m+1, e, x, y );
    return a+b;
}

/*************************** SEGMENT TREE END ***************************/

/*************************** QUERY AND UPDATE START ********************/

int n;
LCA lca;

void update( int x, int v )
{
    data[ Index[x] ] = v;
    update_tree(1, 1, n, Index[x], v);
}

int query_up( int x, int p )
{
    int ans = 0;
    while(1)
    {
        if( chainNo[x] == chainNo[p] )
        {
            ans += query_tree( 1, 1, n, Index[p], Index[x] );
            break;
        }
        int l = Index[x] - posChain[x] + 1, r = Index[x];
        ans += query_tree( 1, 1, n, l, r );
        x = parent[chainHead[ chainNo[x] ]];
    }
    return ans;
}


int query( int x, int y )
{

    int p = lca.find_lca(x, y);
    int a = query_up( x, p );
    int b = query_up( y, p );
    return a+b-data[ Index[p] ];
}
/*************************** QUERY AND UPDATE END ********************/

int temp[M];

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    //filein;
    int t, caseno = 1;
    //cin >> t;
    scanf("%d", &t);
    while(t--)
    {

        cin >> n;
        for( int i =1; i <= n; i++ ) //for multi test case
            edge[i].clear();
        memset( chainLen, 0, sizeof chainLen );

        for( int i = 1; i <= n; i++ )
            cin >> temp[i]; // value of vertex i
        for( int i = 1, a, b; i < n; i++ )
        {
            cin >> a >> b; //input was 0 based vertex
            a++;
            b++;
            edge[a].pb(b);
            edge[b].pb(a);
        }

        level[1] = 0;
        dfs(1,-1);

        chain = 1;
        cur = 1;
        create_hld(1);
        lca.setLCA(n, 1);
        lca.create(parent, level);

        for( int i = 1; i <= n; i++ )
        {
            data[ Index[i] ] = temp[i];
        }
        /*for( int i = 1; i <= n; i++ )
        {
            cout << chainNo[i] << " " << posChain[i] << " " << Index[i] << " " <<  data[i] << endl;
        }*/

        init_tree(1, 1, n);
        int q;
        cin >> q;
        cout << "Case " << caseno++ << ":" << endl;
        int a, b, c;
        while(q--)
        {
            cin >> a >> b >> c;
            if( !a )
            {
                c++;
                b++;
                int ans = query( b, c );
                cout << ans << endl;
            }
            else
            {
                b++;
                update(b, c);
            }
        }
    }
    return 0;
}
