#include<bits/stdc++.h>

using namespace std;

#define intl unsigned long long
#define pii pair<int, int>
#define mp make_pair
#define xx first
#define yy second

const int MAXN = 1e6 + 10;



struct PalindromicTree
{
    struct Node
    {
        int len;
        int cnt;
        int next[26];
        int sufflink;
    };
    string s;
    int Totnode, curnode;
    vector<Node> node;
    vector< vector<int> > suffRG;

    void createNode(int n)
    {
        node[n].len = node[n].cnt = 0;
        memset(node[n].next, -1, sizeof node[n].next);
    }
    void init(int N)
    {
        node.resize(N+5);
        suffRG.resize(N+5);
        for( int i = 1; i < N+5; i++ ) suffRG[i].clear();
        s = "";
        createNode(1);
        createNode(2);
        node[1].sufflink = node[2].sufflink = 1;
        node[1].len = -1;
        node[2].len = 0;
        suffRG[1].push_back(1);
        suffRG[1].push_back(2);
        Totnode = curnode = 2;
    }

    void extend(char ch)
    {
        s += ch;
        int ind = ch - 'a';
        int suff, len = s.length();
        while( len - node[curnode].len - 2 < 0 || s[ len - node[curnode].len - 2 ] != s[len-1] )
            curnode = node[curnode].sufflink;
        suff = node[curnode].sufflink;
        while( len - node[suff].len - 2 < 0 || s[ len - node[suff].len - 2 ] != s[len-1] )
            suff = node[suff].sufflink;
        if( node[curnode].next[ind] == -1 )
        {
            node[curnode].next[ind] = ++ Totnode;
            createNode(Totnode);
            node[Totnode].len = node[curnode].len + 2;
            node[Totnode].sufflink = (node[Totnode].len == 1)? 2: node[suff].next[ind];
            suffRG[ node[Totnode].sufflink ].push_back( Totnode );
        }
        curnode = node[curnode].next[ind];
        node[curnode].cnt++;
    }
};


PalindromicTree pt;


int main()
{
    string s;
    cin >> s;
    pt.init( n );
    for( int i = 0; i < n; i++ )
    {
        pt.extend(s[i]);
    }
    return 0;
}

