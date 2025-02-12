#include<bits/stdc++.h>

using namespace std;

const int MAXN = 300005, sigma = 26;

struct AhoCorasick
{
    struct State
    {
        int to[sigma];
        int go[sigma];
        int par;
        int suffLink;
        int cnt;
        int toLet; //via whitch letter did this node came
        int depth;
    };
    vector<State> node;
    //State node[MAX];
    int nodeCount;
    int root;
    vector< vector<int> > suffRG;

    inline int index( char ch )
    {
        return ch - 'a';
    }
    inline void create( int i )
    {
        //suffRG[i].clear();
        node[i].cnt = 0;
        for( int j = 0; j < sigma; j++ )
            node[i].to[j] = node[i].go[j] = -1;
    }
    void init( int n = MAXN )
    {
        node.resize(n+1);
        suffRG.resize(n+1);
        nodeCount = 0;
        create(++nodeCount);
        root = 1;
        node[root].depth = 0;
        node[root].par = 0;
        for( int i = 0; i < n; i++ )
            suffRG[i].clear();
    }
    int add(const char *str ) //returns the node it is added
    {
        int cur = root;//, len = strlen(str);
        for( int i = 0; str[i]; i++ )
        {
            int v = index(str[i]);
            if( node[cur].to[v] == -1 )
            {
                create(++nodeCount);
                node[cur].to[v] = nodeCount;
                node[nodeCount].par = cur;
                node[nodeCount].depth = node[cur].depth+1;
            }

            cur = node[cur].to[v];
            node[cur].toLet = v;

        }
        return cur;
    }
    void suffLink()
    {
        int cur = root;
        queue<int>q;
        q.push(cur);
        while( !q.empty() )
        {
            int u = q.front();
            q.pop();
            int last = node[u].toLet;
            if( node[u].depth <= 1 )
            {
                node[u].suffLink = 1;
            }
            else
            {
                int cur = node[ node[u].par ].suffLink;
                while( cur > 1 && node[cur].to[last] == -1  )
                {
                    cur = node[cur].suffLink;
                }
                if( node[cur].to[last] != -1)
                    cur = node[cur].to[last];
                node[u].suffLink = cur;
            }
            if( u != 1 )
            {
                suffRG[node[u].suffLink].push_back(u);
            }
            for( int i = 0; i < sigma; i++ )
            {
                if( node[u].to[i] != -1 )
                    q.push(node[u].to[i]);
            }

        }
    }

    inline int nextState(int u, int v)
    {
        if( node[u].go[v] != -1 )
            return node[u].go[v];
        if( node[u].to[v] != -1 )
            return node[u].go[v] = node[u].to[v];
        if( u == 1)
            return node[u].go[v] = max( node[u].to[v], 1 );
        return node[u].go[v] = nextState(node[u].suffLink, v);
    }

    void dfs( int u, int p )
    {
        for( int i = 0; i < suffRG[u].size(); i++ )
        {
            int v = suffRG[u][i];
            if( v == p ) continue;
            dfs(v, u);
            node[u].cnt += node[v].cnt;
        }
    }
};

char str[1000005];
char s[505];
int ind[505];

int main()
{
    //freopen("input.txt", "r", stdin);
    int t, caseno = 1;
    scanf("%d", &t);
    AhoCorasick ac;
    while(t--)
    {
        ac.init(505*508);
        int n;
        scanf("%d", &n);
        scanf("%s", str);
        for( int i = 1; i <= n; i++ )
        {
            scanf("%s", s);
            ind[i] = ac.add(s);
        }
        ac.suffLink();
        int u = ac.root;
        for( int i = 0; str[i]; i++ )
        {
            int v = str[i] - 'a';
            u = ac.nextState(u,v);
            ac.node[u].cnt++;
        }
        ac.dfs(1,-1);
        printf("Case %d:\n", caseno++);
        for( int i = 1; i <= n; i++ )
        {
            printf("%d\n", ac.node[ind[i]].cnt);
        }
    }

    return 0;
}
