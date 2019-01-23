#include <bits/stdc++.h>
using namespace std;
#define MAXL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
#define intl long long
#define pb push_back


bool mark[50000];
intl prime[10000], Pt = 0;
const intl LIM = LLONG_MAX, mod = 1000000007;

void sieve()
{
    prime[Pt++] = 2;
    int n = 47000;
    for( intl i = 3; i <= n; i++ )
    {
        if( mark[i] == 0 )
        {
            prime[Pt++] = i;
            for( intl j = i*i; j <= n; j += i )
                mark[j] = 1;
        }
    }
}

intl mul( intl a, intl b, intl mod)
{
    intl x, res;
    if (a < b) swap(a, b);
    if (!b) return 0;
    if (a < (LIM / b)) return ((a * b) % mod);

    res = 0, x = (a % mod);
    b %= mod;
    while (b)
    {
        if (b & 1)
        {
            res = res + x;
            if (res >= mod) res -= mod;
        }
        b >>= 1;
        x <<= 1;
        if (x >= mod) x -= mod;
    }
    return res%mod;
}

intl expo(intl x, intl n, intl mod)
{
    intl res = 1;
    while (n)
    {
        if (n & 1)
            res = mul(res, x, mod);
        x = mul(x, x, mod);
        n >>= 1;
    }
    return (res % mod);
}

intl gcd(intl x, intl y)
{
    if( y > x ) swap(x, y);
    while( y )
    {
        intl t = x%y;
        x = y;
        y = t;
    }
    return x;
}

int isPrime( intl n )
{
    if( n == 2 )
        return 1;
    if( n % 2 == 0 )
        return 0;
    intl d = n-1;
    while(d%2==0)
        d >>= 1;
    int test[] = {2,3,5,7,11,13,17,19,23};
    for( int i = 0; i < 9; i++ )
    {
        intl x = test[i]%(n-2), temp = d;
        if(x < 2) x += 2;
        intl a = expo(x,d,n);
        while( temp != n-1 && a != 1 && a != n-1 )
        {
            a = mul(a,a,n);
            temp <<= 1;
        }
        if( a != n-1 && (temp&1) ==0 )
            return 0;
    }
    return 1;
}

intl pollard_rho(intl n, intl c)
{
    intl x = 2, y = 2, i = 1, k = 2, d;
    while (true)
    {
        x = ( mul(x, x, n) + c);
        if (x >= n)	x -= n;
        d = gcd( abs(x - y), n);
        if (d > 1) return d;
        if (++i == k)
        {
            y = x;
            k <<= 1;
        }
    }
    return n;
}

void llfactorize(intl n, vector<intl> &f)
{
    if (n == 1)
        return ;
    if (n < 1e9)
    {
        for (int i = 0; prime[i]*prime[i] <= n; i++)
        {
            while (n%prime[i] == 0)
            {
                f.push_back(prime[i]);
                n /= prime[i];
            }
        }
        if (n != 1)	f.push_back(n);
        return ;
    }
    if (isPrime(n))
    {
        f.push_back(n);
        return ;
    }
    intl d = n;
    for (int i = 2; d == n; i++)
        d = pollard_rho(n, i);
    llfactorize(d, f);
    llfactorize(n/d, f);
}

void factorize( intl n, vector< pair<intl,intl> > &ans )
{
    vector<intl> v;
    llfactorize(n, v);
    sort( v.begin(), v.end() );
    intl a = v[0], b = 1;
    for( int i = 1; i < (int)v.size(); i++ )
    {
        if( v[i] == v[i-1] )
            b++;
        else
        {
            ans.pb( make_pair(a,b) );
            a = v[i];
            b = 1;
        }
    }
    ans.pb( make_pair(a,b) );
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    sieve();
    int t;
    intl n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        vector< pair<intl, intl> >ans;
        factorize( n, ans );
        intl val = 1;
        for( int i = 0; i < (int)ans.size(); i++ )
        {
            pair<intl,intl> a = ans[i];
            intl p = a.first, q = a.second;
            cout << p << "^" << q << " * ";
        }
        cout << endl;
    }
    return 0;
}
