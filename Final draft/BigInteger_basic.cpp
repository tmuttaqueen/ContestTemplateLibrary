#include<bits/stdc++.h>

using namespace std;

class BigInteger
{
    int MAXSIZE = 1111;
    int len;
    int* digit;
public:
    BigInteger( int a = 0 )
    {
        digit = new int[MAXSIZE]();
        len = 0;
        if( a == 0 )
        {
            len++;
        }
        int i = MAXSIZE-1;
        while( a > 0 )
        {
            digit[i--] = a%10;
            a/=10;
            len++;
        }
    }
    BigInteger( const char *str )
    {
        digit = new int[MAXSIZE]();
        len = strlen(str);
        int i = MAXSIZE-1;
        for( int j = len-1; j >= 0; j-- )
        {
            digit[i--] = str[j] - '0';
        }
    }
    BigInteger( int* ara, int sz )
    {
        digit = new int[MAXSIZE]();
        len = sz--;
        for( int i = MAXSIZE-1; sz >= 0; i-- )
        {
            digit[i] = ara[sz--];
        }
    }
    BigInteger( const BigInteger &a )
    {
        digit = new int[MAXSIZE];
        len = a.len;
        int c1 = MAXSIZE-1, c2 = a.MAXSIZE-1;
        for( int i = 0; i < a.len; i++ )
        {
            digit[c1--] = a.digit[c2--];
        }
    }

    void print()
    {
        for( int i = MAXSIZE-len; i < MAXSIZE; i++ )
        {
            cout << digit[i];
        }
        cout << endl;
    }

    BigInteger operator+( const BigInteger &b )
    {
        BigInteger ans(0);
        int c = 0;
        int sz = max( len, b.len );
        ans.len = sz;
        for( int i = 1; i <= sz; i++ )
        {
            int d = digit[MAXSIZE-i]+b.digit[MAXSIZE-i]+c;
            ans.digit[MAXSIZE-i] = d%10;
            c = d/10;
        }
        if( c > 0 )
        {
            ans.len++;
            ans.digit[MAXSIZE-ans.len] = c;
        }
        return ans;
    }

    BigInteger operator*( const BigInteger &b )
    {
        BigInteger ans(0);
        int indAns = MAXSIZE-1;
        for( int i = 1; i <= b.len; i++ )
        {
            int d = b.digit[MAXSIZE-i], c = 0, k = indAns;
            for( int j = MAXSIZE-1; j >= MAXSIZE-len; j-- )
            {
                int v = digit[j]*d+c;
                c = v/10;
                c += (ans.digit[k] + v%10)/10;
                ans.digit[k] = (ans.digit[k] + v%10)%10;
                //cout << d << " " << v << " " << c << " k " << k << "  " << ans.digit[k] << endl;
                k--;
            }
            if( c != 0 )
            {
                ans.digit[k--] = c%10;
                if( c/10 != 0 )
                {
                    ans.digit[k--] = c%100;
                }
            }
            ans.len = MAXSIZE-k-1;
            indAns--;
            //ans.print();
        }
        int cnt = 0;
        for( int i = MAXSIZE-1; i >= MAXSIZE-ans.len; i--  )
        {
            if( ans.digit[i] != 0 )
                cnt++;
        }
        if( !cnt )
            ans.len = 1;
        return ans;
    }

    void operator*=( long long num )
    {
        int c = 0;
        for( int i = MAXSIZE-1; i >= MAXSIZE - len; i-- )
        {
            digit[i] = ( digit[i]*num ) + c;
            c = digit[i]/10;
            digit[i] %= 10;
        }
        int ind = MAXSIZE-len-1;
        while( c > 0 )
        {
            digit[ind] = c%10;
            len++;
            ind--;
            c /= 10;
        }
    }

};


int main()
{
    ///initiallize
    int ara[] = {1,5};
    BigInteger a(10), b("13"), c( ara, 2 );
    a.print();
    b.print();
    c.print();
    ///operation +
    BigInteger d = a+b;
    d.print();
    ///operation *
    BigInteger e = b*c;
    e.print();
    ///operator *=
    c *= 10;
    c.print();
    return 0;
}




















