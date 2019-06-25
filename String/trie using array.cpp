#include <bits/stdc++.h>

using namespace std;

const int maxn = 100010;

///returns int value of a character
inline int code(char c)
{
    if (islower(c))
        return c - 'a' + 26;
    return c - 'A';
}

struct Trie
{
    bool is_word;
    int counter;
    int edges[52];
};

int N = 0;
Trie t[maxn];

void init(int v)
{
    t[v].is_word = false;
    t[v].counter = 0;
    memset(t[v].edges, -1, sizeof t[v].edges);
    N++;
}

void add_word(const string & s)
{
    int m = s.size();
    int v = 0;

    for (int i = 0; i < m; i++)
    {
        int c = code(s[i]);
        if (t[v].edges[c] == -1)
        {
            t[v].edges[c] = N;
            init(N);
        }
        v = t[v].edges[c];
    }
    t[v].is_word = true;
    t[v].counter++;
}

int get_count(string s)
{
    int v = 0;
    int m = s.size();

    for (int i = 0; i < m; i++)
    {
        int c = code(s[i]);
        v = t[v].edges[c];

        if (v == -1) return 0;
    }

    return t[v].counter;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        N = 0;
        init(N);

        int n;
        cin >> n;

        string s;
        for (int i = 0; i < n; i++)
        {
            cin >> s;
            if (s.size() > 2)
                sort(++s.begin(), --s.end());
            add_word(s);
        }

        int m;
        cin >> m;
        cin.get();

        printf("Case %d:\n", tc);
        for (int i = 0; i < m; i++)
        {
            getline(cin, s);
            stringstream ss(s);

            int ans = 1;
            while (ss >> s)
            {
                if (s.size() > 2)
                    sort(++s.begin(), --s.end());
                ans *= get_count(s);
            }
            printf("%d\n", ans);
        }
    }

    return 0;
}
