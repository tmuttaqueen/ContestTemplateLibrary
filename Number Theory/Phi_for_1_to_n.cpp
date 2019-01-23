///SIEVE+EULER TOTIENT O(nlogn)
// calculate phi(a) where 1 <= a <= n
// if phi[a] = a-1 then a is a prime

void sieve(int n, int phi[])
{
    for( int i = 1; i < n; i++ )
        phi[i] = i;
    for( int i = 2; i < n; i++ )
    {
        if( phi[i] == i )
        {
            for( int j = i; j < n; j+=i )
            {
                phi[j]/=i;
                phi[j]*= (i-1);
            }
        }
    }
}
