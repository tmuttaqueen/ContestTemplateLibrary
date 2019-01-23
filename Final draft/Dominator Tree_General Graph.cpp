#include<bits/stdc++.h>
using namespace std ;

/* Dominator Tree for General Graph
Tr[u] stores all the immediate children of
node u (does not store the parent)
in the dominator tree */

const int N = 102400;
vector <int> G[N], pred[N], dom[N], Tr[N] ;
int old[N], dfn[N], up[N], f[N], semi[N], g[N], idom[N], cnt ;
int n, m ;

void init()
{
    for (int i = 0 ; i < N ; i++)
        G[i].clear(), pred[i].clear(), dom[i].clear(), Tr[i].clear() ;
    memset (old, 0, sizeof old) ;
    memset (dfn, 0, sizeof dfn) ;
    memset (f, 0, sizeof f) ;
    memset (up, 0, sizeof up) ;
    memset (old, 0, sizeof old) ;
    memset (g, 0, sizeof g) ;
    memset (idom, 0, sizeof idom) ;
    cnt = 0 ;
}


void dfs(int u)
{
    old[dfn[u]=++cnt] = u ;
    semi[cnt] = g[cnt] = f[cnt] = cnt;
    for(int v : G[u])
    {
        if(!dfn[v])
        {
            dfs(v);
            up[dfn[v]] = dfn[u];
        }
        pred[dfn[v]].push_back(dfn[u]);
    }
}

int ff(int x)
{
    if(x == f[x])
        return x;
    int y = ff(f[x]) ;
    if(semi[g[x]] > semi[g[f[x]]])
        g[x] = g[f[x]];
    return f[x] = y;
}

void dominator(int r)
{
    dfs(r);
    for(int y = cnt ; y >= 2 ; y--)
    {
        for(int z : pred[y])
        {
            ff(z);
            semi[y]=min(semi[y],semi[g[z]]);
        }
        dom[semi[y]].push_back(y);
        int x=f[y]=up[y];
        for(int z:dom[x])
        {
            ff(z);
            idom[z]=semi[g[z]]<x? g[z]:x;
        }
        dom[x].clear();
    }
    for(int y = 2 ; y <= cnt ; ++y)
    {
        if(idom[y]!=semi[y])
            idom[y]=idom[idom[y]];
        dom[idom[y]].push_back(y);
    }
    idom[r] = 0 ;
    for (int i = 1 ; i <= n ; i++)
    {
        for (int j = 0 ; j < dom[i].size() ; j++)
        {
            Tr[old[i]].push_back(old[dom[i][j]]) ;
        }
    }
}

int main()
{
    init() ;
    scanf("%d %d",&n,&m);
    for (int i = 1 ; i <= m ; i++)
    {
        int u, v ;
        scanf("%d %d",&u,&v) ;
        G[u].push_back(v) ;
    }
    dominator(1) ;
}
