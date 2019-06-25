#include<bits/stdc++.h>

using namespace std;

struct node
{
    int d;
    node *next[26];
    node()
    {
        d = 0;
        for( int i = 0; i < 26; i++ )
            next[i] = NULL;
    }
};

void insert( string s, node *root )
{
    node *cn = root;
    for( int i = 0; i < s.size(); i++ )
    {
        if( cn->next[ s[i]- 'a' ] == NULL )
            cn->next[s[i]- 'a'] = new node;
        cn = cn->next[s[i]- 'a'];
    }
    cn->d = cn->d + 1;
    return;
}

int exist( string s, node *root )
{
    node *cn = root;
    for( int i = 0; i < s.size(); i++ )
    {
        if( cn->next[ s[i]-'a' ] == NULL )
            return 0;
        cn = cn->next[ s[i]-'a' ];
    }
    return cn->d;
}

int main()
{
    freopen( "input.txt", "r", stdin );
    node *root = new node;
    int n, k;
    cin >> n >> k;
    for( int i = 0; i < n; i++ )
    {
        string s;
        cin >> s;
        insert( s, root );
    }
    for( int i = 0; i < k; i++ )
    {
        string s;
        cin >> s;
        cout << s << "  ";
        cout << exist( s, root ) << endl;
    }
    return 0;
}
