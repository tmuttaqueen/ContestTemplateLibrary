/**************************************************************************************
    Palindrome tree. Useful structure to deal with palindromes in strings. O(N)
    This code counts number of palindrome substrings of the string.
    Based on problem 1750 from informatics.mccme.ru:
    http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=1750
**************************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <utility>
#include <cstring>
#include <cassert>
#include <cmath>
#include <stack>
#include <queue>

using namespace std;

const int MAXN = 105000;
char s[MAXN];

struct node
{
    int next[26];
    int len;
    int sufflink;
    //if you need extra information keep here
};

struct PLTree
{
    int len;
    node *tree;
    int num;  // node 1 - root with len -1, node 2 - root with len 0
    int suff; // max suffix palindrome of the string so far while traversing
    PLTree(int mx = 105000)
    {
        tree = new node[mx];
        initTree();
    }
    void initTree()
    {
        num = 2;
        suff = 2;
        tree[1].len = -1;
        tree[1].sufflink = 1;
        tree[2].len = 0;
        tree[2].sufflink = 1;
    }
    void addLetter(int pos, char ch)
    {
        int cur = suff, curlen = 0;
        int let = ch - 'a';
        while (true)
        {
            curlen = tree[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
                break;
            cur = tree[cur].sufflink;
        }
        if (tree[cur].next[let])
        {
            suff = tree[cur].next[let];
            return;
        }

        num++;
        suff = num;
        tree[num].len = tree[cur].len + 2;
        tree[cur].next[let] = num;

        if (tree[num].len == 1)
        {
            tree[num].sufflink = 2;
            return;
        }

        while (true)
        {
            cur = tree[cur].sufflink;
            curlen = tree[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
            {
                tree[num].sufflink = tree[cur].next[let];
                break;
            }
        }
        return;
    }
};



int main()
{
    //assert(freopen("input.txt", "r", stdin));
    //assert(freopen("output.txt", "w", stdout));

    gets(s);
    int len = strlen(s);

    initTree();

    for (int i = 0; i < len; i++)
    {
        addLetter(i);
        ans += tree[suff].num;
    }

    cout << ans << endl;

    return 0;
}
