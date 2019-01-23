#include <bits/stdtr1c++.h>

using namespace std;

const int MAX = 105;

namespace wm
{
bool visited[MAX];
int U[MAX], V[MAX], P[MAX], way[MAX], minv[MAX], match[MAX], ar[MAX][MAX];
/// n = number of row and m = number of columns in 1 based, flag = 1-MAXIMIZE or 0-MINIMIZE
/// match[i] contains the column to which row i is matched
int hungarian(int n, int m, int mat[MAX][MAX], int flag = 0)
{
    memset(U, 0, sizeof(U));
    memset(V, 0, sizeof(V));
    memset(P, 0, sizeof(P));
    memset(ar, 0, sizeof(ar));
    memset(way, 0, sizeof(way));
    int inf = 1e9;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            ar[i][j] = mat[i][j];
            if (flag) ar[i][j] = -ar[i][j];
        }
    }
    if (n > m) m = n;

    int i, j, a, b, c, d, r, w;
    for (i = 1; i <= n; i++)
    {
        P[0] = i, b = 0;
        for (j = 0; j <= m; j++) minv[j] = inf, visited[j] = false;

        do
        {
            visited[b] = true;
            a = P[b], d = 0, w = inf;

            for (j = 1; j <= m; j++)
            {
                if (!visited[j])
                {
                    r = ar[a][j] - U[a] - V[j];
                    if (r < minv[j]) minv[j] = r, way[j] = b;
                    if (minv[j] < w) w = minv[j], d = j;
                }
            }

            for (j = 0; j <= m; j++)
            {
                if (visited[j]) U[P[j]] += w, V[j] -= w;
                else minv[j] -= w;
            }
            b = d;
        }
        while (P[b] != 0);

        do
        {
            d = way[b];
            P[b] = P[d], b = d;
        }
        while (b != 0);
    }
    for (j = 1; j <= m; j++) match[P[j]] = j;

    return (!flag) ? -V[0] : V[0];
}
}

int ara[MAX][MAX];

int main()
{
    int n = 3, m = 4;
    for( int i = 1; i <= n; i++ )
    {
        ara[i][i+1] = 1;
        int f = 2;
        for( int j = 1; j <= m; j++ )
        {
            if( j == i+1 ) continue;
            ara[i][j] = f++;
        }
    }
    cout << wm::hungarian(n, m, ara) << endl;
    for( int i = 1; i <= n; i++ )
        cout << wm::match[i] << endl;

    return 0;
}
