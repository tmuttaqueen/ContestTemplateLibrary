#include <bits/stdc++.h>

using namespace std;

const double pi = 3.141592653589793;

#define xx          first
#define yy          second
#define mp          make_pair
#define intl        long long
#define filein      freopen("input.txt", "r", stdin)
#define fileout     freopen("output.txt", "w", stdout)
#define debug       printf("yes\n")
#define val_of(x)   cout << #x << " is " << x << "   "
#define what_is(x)  cout << #x << " is " << x << endl
#define pb          push_back
#define eb          emplace_back
#define pii         pair<int, int>
#define piii        pair<pii, int>
#define double      long double


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

    for( int i = 0; i < 10; i++ )
    {
        long long x = 2 + rand()%(n-2), temp = d;
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

int main()
{
    ios::sync_with_stdio(false);
    //filein;
    if( is_prime(10) )
        cout << "yes\n";
    else
        cout << "no\n";
    if( is_prime(25) )
        cout << "yes\n";
    else
        cout << "no\n";
    if( is_prime(1000000007) )
        cout << "yes\n";
    else
        cout << "no\n";
    if( is_prime(2) )
        cout << "yes\n";
    else
        cout << "no\n";
    if( is_prime(17) )
        cout << "yes\n";
    else
        cout << "no\n";
    cout << "finish\n";

    return 0;
}




