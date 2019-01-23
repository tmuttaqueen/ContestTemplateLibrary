///1D BIT O(logn)
const int mx = 100002;
int bit[mx];
void update( int x, int val ) //add val to index x
{
    while( x <= mx )
    {
        bit[x] += val;
        x += (x&(-x));
    }
}

int query( int x ) //sum from 1 to x (inclusive)
{
    int sum = 0;
    while( x > 0 )
    {
        sum += bit[x];
        x -= (x&(-x));
    }
    return sum;
}

///2D BIT O(log^2n)
const int mx = 1002;
int bit[mx][mx];
void update( int x, int y, int val ) //add val to (x,y)
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

int query( int x, int y ) //sum from (1,1) to (x,y) (inclusive)
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
