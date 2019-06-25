///1D BIT O(logn)
///range update point query
struct BIT1D
{
    int mx;
    vector<int>bit;
    void init( int n = 1002 )
    {
        mx = (n+2);
        bit.resize(mx,0);
    }
    void update( int x, int val ) //add val to index x
    {
        while( x <= mx )
        {
            bit[x] += val;
            x += (x&(-x));
        }
    }

    int query( int x ) //value of x
    {
        int sum = 0;
        while( x > 0 )
        {
            sum += bit[x];
            x -= (x&(-x));
        }
        return sum;
    }
    void update( int from, int to, int val ) //for range update
    {
        update( from, val );
        update( to+1, -val );
    }
};
