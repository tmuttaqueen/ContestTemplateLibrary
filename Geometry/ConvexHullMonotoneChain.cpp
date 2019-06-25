const int MX = 111111;
int N, H;
pair<intl, intl>point[MX];
pair<intl, intl>hull[MX];

intl cross( pair<intl, intl> &a, pair<intl, intl> &b, pair<intl, intl> &c )
{
    return (b.xx-a.xx)*(c.yy-a.yy) - (b.yy-a.yy)*(c.xx-a.xx);
}

void monotoneChain()
{
    H = 0;
    sort( point, point+N );
    for( int i = 0; i < N; i++ )
    {
        while( H >= 2 && cross( hull[H-2], hull[H-1], point[i] ) <= 0 )
        {
            H--;
        }
        hull[H++] = point[i];
    }
    int f = H-1;
    for( int i = N-1; i >= 0; i-- )
    {
        while( H-f >= 2 && cross( hull[H-2], hull[H-1], point[i] ) <= 0 )
        {
            H--;
        }
        hull[H++] = point[i];
    }
    if( hull[H-1] == hull[0] )
    {
        H--;
    }
}

