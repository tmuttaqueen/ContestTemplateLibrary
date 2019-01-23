///DINIC EDGE LIST

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

