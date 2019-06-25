#include <bits/stdc++.h>

using namespace std;

const int mx = 10005;
int arr[mx], rmq[mx][20];

void preprocess()
{
    for( int i = 0; i <= 10000; i++ )
        rmq[i][0] = i;   ///save index of the minimun number, if u want value save the value
    for( int i = 1; (1<<i) <= mx; i++ )
    {
        for( int j = 0; (i+(1<<j)-1) <= mx; j++ )
        {
            if( arr[ rmq[j][i-1] ] < arr[ rmq[j+(1<<i)-1][i-1] ] ) /// if u want value save the value change here
                rmq[j][i] = rmq[j][i-1];
            else
                rmq[j][i] = rmq[j+(1<<i)-1][i-1];
        }
    }
}

int query( int u, int v )
{
    int k = log(1.0*v - 1.0*u + 1)/log(2.0);
    int ans = min( arr[ rmq[u][k] ], arr[ rmq[v-(1<<k)+1][k] ] );
    return ans;
}

int main()
{
    arr[0] = 2;
    arr[1] = 242;
    arr[3] = 1;
    arr[4] = 43;
    preprocess();
    cout << query(0,1) << endl;
}
