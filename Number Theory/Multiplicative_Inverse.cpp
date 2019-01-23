///MULTIPLICATIVE_INVERSE (1/a) % mod
///only exist when gcd(a, mod) = 1


///Using Extended Euclid O(logn)
// if (1/a)%mod = x then ax + mod*y = 1

long long g, x, y; //x is the answer
void mul_inverse( long long a, long long mod)
{
    if(mod == 0)
    {
        g = a;
        x = 1;
        y = 0;
        return;
    }
    mul_inverse( mod, a%mod );
    long long temp = x;
    x = y;
    y = temp - (a/mod)*y;
    return;
}


///Using fermat's little theorem O(logn) only when mod is prime
// we know a^(mod-1) % mod = 1 so, a^(mod-2)%mod = (1/a)%mod

long long mul_inverse( long long a, long long mod )
{
    long long b = mod - 2;
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


