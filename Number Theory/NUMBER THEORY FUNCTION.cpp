///EUCLID O(logn)
//computes gcd(a,b)
long long gcd( long long a, long long b )
{
    b == 0? return a: return gcd( b, a%b );
}

///EXTENDED EUCLID O(logn)
//computes x, y, gcd(a,b) for the equation "ax + by = gcd(a,b)"
//if gcd(a,b) = 1 then x is the multiplicative inverse of a mod b that means (a*x)%b = 1;
//if x=Ai mod Mi,i=1,2,3..and gcd(Mi,Mj)=1 then sol: x=(M/M1*Y1*A1+M/M2*Y2*A2+..M/Mi*Yi*Ai)%M,M = lcm(M1, M2...Mi) and (M/Mi*Yi)%M=1 ie. Yi is mudulu inverse of M/Mi
//diap eqn: ax + by = gcd(a,b); if x1, y1 is a solution then all sol: x = x1+b*t, y = y1-a*t

long long g, x, y;
void extendedEuclid( long long a, long long b)
{
    if(b == 0)
    {
        g = a;
        x = 1;
        y = 0;
        return;
    }
    extendedEuclid( b, a%b );
    long long temp = x;
    x = y;
    y = temp - (a/b)*y;
    return;
}

///BINARY EXPONENTIATION O(logn)
//computes (a^b)%mod
//if gcd(a,mod) = 1 then (a^(mod-2))%mod is the multiplicative inverse of a modulu mod

long long exponentiation( long long a, long long b, long long mod )
{
    long long ans = 1;
    while( b > 0 )
    {
        if( b&1 )
            ans = (a*ans)%mod;
        a = (a*a)%mod;
        b /= 2;
    }
    return ans;
}

///MULMOD O(logn)
//determone (a*b)%mod taking into account that a*b might overflow ( here b = 2^b1 + 2^b2 + 2^b3 +.... )

long long mulmod( long long a, long long b, long long mod )
{
    long long x = 0, y = a%mod;
    while( b > 0 )
    {
        if(b&1)
            x = (x+y)%mod;
        y = (y*2)%mod;
        b /= 2;
    }
    return x%mod;
}

///MILLER-ROBIN O(k*logn)
//determine if a number is prime

int is_prime( long long n )
{
    if( n == 2 )
        return 1;
    if( n % 2 == 0 )
        return 0;
    long long d = n-1;
    while(d%2==0)
    {
        d/=2;
    }
    int test[] = {2,3,5,7,11,13,17,19,23,29};
    for( int i = 0; i < 10; i++ )
    {
        unsigned long long x = test[i]%(n-2), temp = d;
        if(x < 2) x += 2;
        //use mulmod() in exponentiation for n>1e9
        long long a = exponentiation(x,d,n);
        while( temp != n-1 && a != 1 && a != n-1 )
        {
            a = mulmod(a,a,n);
            temp *= 2;
        }
        if( a != n-1 && temp%2==0 )
            return 0;
    }
    return 1;
}

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
