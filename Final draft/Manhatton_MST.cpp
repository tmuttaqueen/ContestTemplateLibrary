/// https://www.codechef.com/problems/DRAGONST

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2e5 + 10;
vector<int> adj[maxn], cost[maxn];

int par[maxn][19], ans[maxn][19], L[maxn], n;

struct UnionFind
{
    int p[maxn];
    void init(int n)
    {
        for(int i = 1; i <= n; i++)
            p[i] = i;
    }
    int find(int u)
    {
        return p[u] == u ? u : p[u] = find(p[u]);
    }
    void Union(int u, int v)
    {
        p[find(u)] = find(v);
    }
} dsu;
struct point
{
    int x, y, index;
    bool operator < (const point &p) const
    {
        return x == p.x ? y < p.y : x < p.x;
    }
} p[maxn];
int dist(point &a, point &b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}
struct edge
{
    int u, v, c;
    bool operator < (const edge &p) const
    {
        return c < p.c;
    }
};
struct node
{
    int value, p;
} T[maxn];

int query(int x)
{
    int r = INT_MAX, p = -1;
    for(; x <= n; x += (x & -x))
        if(T[x].value < r)
            r = T[x].value, p = T[x].p;
    return p;
}
void update(int x, int w, int p)
{
    for(; x > 0; x -= (x & -x))
        if(T[x].value > w)
            T[x].value = w, T[x].p = p;
}

vector<edge> edgelist;

void addEdge(int u, int v, int c)
{
    edgelist.push_back({u, v, c});
}
int kruskal()
{
    dsu.init(n);
    sort(edgelist.begin(), edgelist.end());
    for(edge e : edgelist)
    {
        int u = e.u, v = e.v, c = e.c;
        if(dsu.find(u) != dsu.find(v))
        {
            adj[u].push_back(v);
            adj[v].push_back(u);
            cost[u].push_back(c);
            cost[v].push_back(c);
            dsu.Union(u, v);
        }
    }
}
void manhattan()
{
    for(int i = 1; i <= n; ++i)
        p[i].index = i;
    for(int dir = 1; dir <= 4; ++dir)
    {
        if(dir == 2 || dir == 4)
        {
            for(int i = 1; i <= n; ++i)
                swap(p[i].x, p[i].y);
        }
        else if(dir == 3)
        {
            for(int i = 1; i <= n; ++i)
                p[i].x = -p[i].x;
        }
        sort(p + 1, p + 1 + n);
        vector<int> v;
        static int a[maxn];
        for(int i = 1; i <= n; ++i)
            a[i] = p[i].y - p[i].x, v.push_back(a[i]);
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for(int i = 1; i <= n; ++i)
            a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        for(int i = 1; i <= n; ++i)
            T[i].value = INT_MAX, T[i].p = -1;
        for(int i = n; i >= 1; --i)
        {
            int pos = query(a[i]);
            if(pos != -1)
                addEdge(p[i].index, p[pos].index, dist(p[i], p[pos]));
            update(a[i], p[i].x + p[i].y, i);
        }
    }
}

void dfs(int u, int c, int p)
{
    L[u] = L[p] + 1;
    par[u][0] = p;
    ans[u][0] = c;
    for(int i = 1; i <= 18; i++)
    {
        par[u][i] = par[par[u][i-1]][i-1];
        ans[u][i] = max(ans[u][i-1], ans[par[u][i-1]][i-1]);
    }
    for(int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i], c = cost[u][i];
        if(v - p)
            dfs(v, c, u);
    }
}

int pathQuery(int u, int v)
{
    if(L[u] < L[v])
        swap(u, v);
    int ret = 0;
    for(int i = 18; i >= 0; i--)
    {
        if(L[par[u][i]] >= L[v])
        {
            ret = max(ret, ans[u][i]);
            u = par[u][i];
        }
    }
    if(u == v)
        return ret;
    for(int i = 18; i >= 0; i--)
    {
        if(par[u][i] - par[v][i])
        {
            ret = max({ret, ans[u][i], ans[v][i]});
            u = par[u][i], v = par[v][i];
        }
    }
    return max({ret, ans[u][0], ans[v][0]});
}
void clear(int n)
{
    memset(par, 0, sizeof par);
    memset(ans, 0, sizeof ans);
    edgelist.clear();
    for(int i = 0; i <= n; i++)
        adj[i].clear(), cost[i].clear();
}
int main(int argc, char const *argv[])
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%d %d", &p[i].x, &p[i].y);
        clear(n);
        manhattan();
        kruskal();
        dfs(1, 0, -1);
        int q;
        scanf("%d", &q);
        while(q--)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            printf("%d\n", pathQuery(u, v));
        }
    }
}
