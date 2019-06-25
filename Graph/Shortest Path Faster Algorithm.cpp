#include<bits/stdc++.h>

using namespace std;

const int M = 100;
vector< pair<int,int> >edge[M];
int par[M];

bool spfa( int s, int dist[], int vertex )
{
    for( int i = 0; i <= vertex; i++ )
        dist[i] = 1e9;

    bool flag[M], is_neg = 0;
    int relax[M];
    memset( flag, 0, sizeof flag );
    memset( relax, 0, sizeof relax );

    dist[s] = 0;
    queue<int>Q;
    Q.push(s);
    relax[s]++;
    flag[s] = 1;
    par[s] = -1;
    while( !Q.empty() )
    {
        int u = Q.front();
        Q.pop();
        if( relax[u] >= vertex )
        {
            is_neg = 1;
            break;
        }
        flag[u] = 0;
        for( int i = 0; i < edge[u].size(); i++ )
        {
            int v = edge[u][i].first, w = edge[u][i].second;
            if( dist[v] > dist[u] + w && v != par[u] )
            {
                dist[v] = dist[u] + w ;
                if( flag[v] == 0 )
                {
                    par[v] = u;
                    Q.push(v);
                    flag[v] = 1;
                    relax[v]++;
                }
            }
        }
    }

    return is_neg;
}

int myrandom(int x)
{
    return rand()*23%x;
}

int main()
{
    int v, e, a, b, w;
    cin >> v >> e;
    for( int i = 0; i < e; i++ )
    {
        cin >> a >> b >> w;
        edge[a].push_back( make_pair(b, w) );
        edge[b].push_back( make_pair(a, w) );
    }
    for( int i = 1; i <= v; i++ )
    {
        random_shuffle( edge[i].begin(), edge[i].end(), myrandom );
    }
    int dist[M];
    int f = spfa(1, dist, v);
    cout << f << endl;
    for( int i = 1; i <= v; i++ ) cout << dist[i] << " ";
}
