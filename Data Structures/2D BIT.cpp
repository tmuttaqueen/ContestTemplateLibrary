#include <bits/stdc++.h>
using namespace std;

const int mx = 1002;

int bit[mx][mx];

void update( int x, int y, int val ) // update the value of (x,y)
{
    int temp = y;
    while( x < mx )
    {
        y = temp;
        while( y < mx )
        {
            bit[x][y] += val;
            y += (y&(-y));
        }
        x += (x&(-x));
    }
}

int query( int x, int y ) //sum of all numbers from (0,0) to (x,y) (inclusive)
{
    int temp = y, sum = 0;
    while( x > 0 )
    {
        y = temp;
        while( y > 0 )
        {
            sum += bit[x][y];
            y -= (y&(-y));
        }
        x -= (x&(-x));
    }
    return sum;
}

int main()
{
    update( 1,1,1 );
    update( 2,2,1 );
    update( 3,3,1 );
    update( 4,4,1 );
    cout << query(2,2) << "  " << query(4,4) << endl;
}



