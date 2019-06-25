///ARTICULATION POINT IN UNDIRECTED GRAPH O(V+E)

const int mx = 100000;
vector<int>edge[mx];
vector<int>discovery(mx), low(mx), vis(mx), is_art(mx), parent(mx);
int childroot = 0;
//memset on edge[mx], vis(mx), is_art(mx), childroot
void dfs( int u, int Time = 1 )
{
    if( Time == 1 )
        parent[u] = -1;
    discovery[u] = low[u] = Time++;
    vis[u] = 1;
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( vis[v] == 0 )
        {
            if( parent[u] == -1 )
                childroot++;
            parent[v] = u;
            dfs( v, Time );
            low[u] = min( low[u], low[v] );
            if( parent[u] == -1 && childroot > 1 ) //artculation point check for root
                is_art[u] = 1;
            if( parent[u] != -1 && low[v] >= discovery[u] ) ////artculation point check for rest vertex
                is_art[u] = 1;
        }
        else if( v != parent[u] )
            low[u] = min( low[u], discovery[v] );
    }
}


///BRIDGES IN UNDIRECTED GRAPH O(V+E)

const int mx = 100000;
vector<int>edge[mx];
vector<int>discovery(mx), low(mx), vis(mx), parent(mx);
vector<pii>bridge;
//memset on edge[mx], vis(mx), bridge
void dfs( int u, int Time = 1 )
{
    discovery[u] = low[u] = Time++;
    vis[u] = 1;
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( vis[v] == 0 )
        {
            parent[v] = u;
            dfs( v, Time );
            low[u] = min( low[u], low[v] );
            if( low[v] > discovery[u] ) // bridge check for all u-v (including root)
                bridge.pb( mp(u,v) );
        }
        else if( v != parent[u] )
            low[u] = min( low[u], discovery[v] );
    }
}


///BICONNECTED COMPONENTS IN UNDIRECTED GRAPH O(V+E)

const int mx = 100000;
vector<int>edge[mx];
vector<int>discovery(mx), low(mx), vis(mx), parent(mx);
int childroot = 0;
stack<pii>bicom;
//memset on edge[mx], vis(mx), childroot
void dfs( int u, int Time = 1 )
{
    if( Time == 1 )
        parent[u] = -1;
    discovery[u] = low[u] = Time++;
    vis[u] = 1;
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( vis[v] == 0 )
        {
            if( parent[u] == -1 )
                childroot++;
            parent[v] = u;
            bicom.push( mp(u,v) );
            dfs( v, Time );
            low[u] = min( low[u], low[v] );
            if( (discovery[u] == 1 && childroot > 1) || (discovery[u] > 1 && low[v] >= discovery[u]) )
            {
                cout << "components :\n";
                while( bicom.top() != mp( u, v ) )
                {
                    cout << bicom.top().xx << " " << bicom.top().yy << endl;
                    bicom.pop();
                }
                cout << bicom.top().xx << " " << bicom.top().yy << endl;
                bicom.pop();
            }

        }
        else if( v != parent[u] && discovery[v] < low[u] )
        {
            bicom.push( mp(u,v) );
            low[u] = min( low[u], discovery[v] );
        }

    }
}
void runner( int v )
{
    for( int  i = 0; i < v; i++ )
    {
        if(!vis[i])
        {
            dfs(i);
            cout << "components :\n";
            while( !bicom.empty() )
            {
                cout << bicom.top().xx << " " << bicom.top().yy << endl;
                bicom.pop();
            }
        }
    }
}


///STRONGLY CONNECTED COMPONENT FOR DIRECTED GRAPH O(V+E)

const int mx = 100000;
vector<int>edge[mx], rev_edge[mx], SCC[mx];
int vis[mx], mark;
stack<int>st;
//memset edge, rec_edge, SCC, vis, mark, st
//this dfs sort by finishing time top of stack = higher finishing time
void dfs1( int u )
{
    vis[u] = 1;
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( !vis[v] )
            dfs1( v );
    }
    st.push(u);
}
//this dfs finds SCC
void dfs2( int u )
{
    SCC[mark].pb(u);
    vis[u] = 1;
    for( int i = 0; i < rev_edge[u].size(); i++ )
    {
        int v =rev_edge[u][i];
        if( !vis[v] )
            dfs2( v );
    }
}
//helper function
void find_SCC( int node, int edg )
{
    memset( vis, 0, sizeof vis );
    for( int i = 0; i < node; i++ )
    {
        if( !vis[i] )
            dfs1(i);
    }
    memset( vis, 0, sizeof vis );
    mark = 0;
    while( !st.empty() )
    {
        int u = st.top();
        st.pop();
        if( !vis[u] )
        {
            dfs2(u);
            mark++;
        }
    }
    for(  int i = 0; i < mark; i++ )
    {
        cout << "component :\n";
        for( int j = 0; j < SCC[i].size(); j++ )
            cout << SCC[i][j] << " ";
        cout << endl;
    }
}

///TOPOLOGICAL SORT BY DFS FINISHING TIME O(V+E)

const int mx = 100000;
vector<int>edge[mx];
int vis[mx], in[mx];
stack<int>st;
//memset edge, vis, st
//this dfs sort by finishing time. top of stack = higher finishing time
void dfs( int u )
{
    vis[u] = 1;
    for( int i = 0; i < edge[u].size(); i++ )
    {
        int v = edge[u][i];
        if( !vis[v] )
            dfs( v );
    }
    st.push(u);
}


///EULER_TOUR O(ElogE)
const int mx = 1000;
//memset all everytime
//map is for counting edge between u,v
//tour is the euler tour
vector<int>edge[mx];
vector<int>tour;
map<pii,int>mm;

void euler_tour( int u )
{
    for( int i = edge[u].size() - 1; i >= 0 ; i-- )
    {
        int v = edge[u][i];
        edge[u].pop_back();
        int a = min(u,v),b = max(u,v);//for undirected graph
        if( mm[mp(a,b)] )
        {
            mm[mp(a,b)]--;
            euler_tour(v);
        }
    }
    tour.pb(u);
}





