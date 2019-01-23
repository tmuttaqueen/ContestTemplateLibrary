///********************FFT*********************
#include<bits/stdc++.h>
using namespace std;

struct FFT
{
    struct node
    {
        double x,y;
        node() {}
        node(double a, double b): x(a), y(b) {}
        node operator + (const node &a) const
        {
            return node(this->x+a.x,this->y+a.y);
        }
        node operator - (const node a) const
        {
            return node(this->x-a.x,this->y-a.y);
        }
        node operator * (const node a) const
        {
            return node(this->x*a.x-this->y*a.y,this->x*a.y+a.x*this->y);
        }
    };

    int M;
    vector<node> A, B, w[2];
    vector<int>rev;
    long double pi;
    FFT()
    {
        pi = 3.1415926535897932384;
    }
    void init(int n)
    {
        M = 1;
        while(M < n) M <<= 1;
        M <<= 1;
        A.resize(M);
        B.resize(M);
        w[0].resize(M);
        w[1].resize(M);
        rev.resize(M);
        for (int i=0; i<M; i++)
        {
            int j=i,y=0;
            for (int x=1; x<M; x<<=1,j>>=1) (y<<=1)+=j&1;
            rev[i]=y;
        }
        for (int i=0; i<M; i++)
        {
            w[0][i] = node( cos(2*pi*i/M),sin(2*pi*i/M) );
            w[1][i] = node( cos(2*pi*i/M),-sin(2*pi*i/M) );
        }
    }
    void ftransform( vector<node> &A, int p )
    {
        for (int i=0; i<M; i++)
            if (i<rev[i])
                swap(A[i],A[rev[i]]);
        for (int i=1; i<M; i<<=1)
            for (int j=0,t=M/(i<<1); j<M; j+=i<<1)
                for (int k=0,l=0; k<i; k++,l+=t)
                {
                    node x=w[p][l]*A[i+j+k];
                    node y=A[j+k];
                    A[j+k]=y+x;
                    A[j+k+i]=y-x;
                }
        if (p)
            for (int i=0; i<M; i++)
                A[i].x/=M;
    }
    /// multiply P*Q and keeps the result in res
    ///degree of P is n and degree of Q is m
    ///P, Q is given in standard power form, in increasing
    void multiply( vector<int> &P, vector<int> &Q, vector<int> &res)
    {
        init( max(P.size(),Q.size()) );
        for( int i = 0; i < M; i++ )
            A[i].x = A[i].y = B[i].x = B[i].y = 0;
        for( int i = 0; i < P.size(); i++ )
            A[i].x = P[i];
        for( int i = 0; i < Q.size(); i++ )
            B[i].x = Q[i];
        ftransform(A,0);
        ftransform(B,0);
        for (int k=0; k<M; k++)
            A[k] = A[k]*B[k];
        ftransform(A,1);
        res.resize(M);
        for( int i = 0; i < M; i++ )
            res[i] = (A[i].x + 0.5);
    }

};



///***********************NTT****************************
#include<bits/stdc++.h>

using namespace std;

struct NTT
{
    vector<int>A, B, w[2], rev;
    int P, M, G;

    NTT( int mod )
    {
        P = mod;
        G = 3;
    }
    int Pow(int a, int b)
    {
        int res=1;
        for (; b; b>>=1,a=a*1LL*a%P) if (b&1) res=res*1LL*a%P;
        return res;
    }
    void init( int n )
    {
        for (M=1; M<n; M<<=1);
        M<<=1;
        A.resize(M);
        B.resize(M);
        w[0].resize(M);
        w[1].resize(M);
        rev.resize(M);
        for (int i=0; i<M; i++)
        {
            int x=i, &y=rev[i];
            y=0;
            for (int k=1; k<M; k<<=1,x>>=1)
                (y<<=1)|=x&1;
        }
        int x=Pow(G,(P-1)/M),y=Pow(x,P-2);
        w[0][0]=w[1][0]=1;
        for (int i=1; i<M; i++)
        {
            w[0][i]=w[0][i-1]*1LL*x%P;
            w[1][i]=w[1][i-1]*1LL*y%P;
        }
    }

    void ntransform(vector<int> &a, int f)
    {
        for (int i=0; i<M; i++)
            if (i<rev[i]) swap(a[i],a[rev[i]]);
        for (int i=1; i<M; i<<=1)
            for (int j=0,t=M/(i<<1); j<M; j+=i<<1)
                for (int k=0,l=0; k<i; k++,l+=t)
                {
                    int x=a[j+k+i]*1ll*w[f][l]%P;
                    int y=a[j+k];
                    a[j+k+i]=y-x<0?y-x+P:y-x;
                    a[j+k]=y+x>=P?y+x-P:y+x;
                }
        if (f)
        {
            int x=Pow(M,P-2);
            for (int i=0; i<M; i++) a[i]=a[i]*1ll*x%P;
        }
    }

    void multiply( vector<int> &X, vector<int> &Y, vector<int> &res)
    {
        init(max(X.size(), Y.size()));
        for( int i = 0; i < M; i++ )
            A[i] = B[i] = 0;
        for( int i = 0; i < X.size(); i++ )
            A[i] = X[i];
        for( int i = 0; i < Y.size(); i++ )
            B[i] = Y[i];
        for( int x: A )
            cout << x << " ";
        cout << endl;
        for( int x: B )
            cout << x << " ";
        cout << endl;
        ntransform(A,0);
        ntransform(B,0);
        res.clear();
        res.resize(M);
        for (int i=0; i<M; i++)
            res[i]=A[i]*1LL*B[i]%P;
        ntransform(res,1);
    }
};


int main()
{
    NTT ntt(998244353);
    vector<int>A{0, 2, 0, 1, 2}, B{1, 0, 0, 0, -1, 0, -5};
    ntt.multiply(A,B,A);
    for( int i = 0; i < A.size(); i++)
        cout << A[i] << " ";
    cout << endl;
}


///***************** OR CONVOLUTION ***********************************

const int mod = 1e8 + 7;
struct ORconvolution
{
    long long poww(long long a, long long b, long long mod)
    {
        long long ans = 1;
        while (b > 0)
        {
            if (b & 1) ans = (ans * a) % mod;
            b >>= 1;
            a = (a * a) % mod;
        }
        return ans;
    }

    void ORtransform(vector<long long> &vec, bool inverse = 0)
    {
        for(int len = 1; 2 * len <= vec.size(); len <<= 1)
        {
            for(int i = 0; i < vec.size(); i += 2 * len)
            {
                for(int j = 0; j < len; j++)
                {
                    long long u = vec[i + j];
                    long long v = vec[i + len + j];
                    if( !inverse )
                    {
                        vec[i + j] = u + v;
                        vec[i + len + j] = u;//%mod;
                    }
                    else
                    {
                        vec[i + j] = v;//%mod;
                        vec[i + len + j] = u - v;
                    }
                }
            }
        }
    }
    //input: two vector denoting coefficient of a polynomial
    //output: a vector denoting their multiplication x^a*x^b = x^(a or b)
    vector<long long> multiply( vector<long long> v1, vector<long long>v2 )
    {
        int d = 1, dd = max( v1.size(), v2.size() );
        while(d<dd)
            d*=2;
        v1.resize(d, 0);
        v2.resize(d, 0);
        vector<long long>res(d, 0);
        ORtransform(v1, 0);
        ORtransform(v2, 0);
        for( int i = 0; i < d; i++ ) res[i] = v1[i]*v2[i];
        ORtransform(res, 1);
        return res;
    }
    //input: two vector denoting coefficient of a polynomial
    //output: a vector denoting (poly)^n
    vector<long long> multiply( vector<long long>v1, int n )
    {
        int d = 1, dd = v1.size();
        while(d<dd)
            d*=2;
        v1.resize(d, 0);
        vector<long long>res(d, 0);
        ORtransform(v1, 0);
        for( int i = 0; i < d; i++ ) res[i] = poww( v1[i], n, mod );
        ORtransform(res, 1);
        return res;
    }

};


///************************ AND CONVOLUTION ************************************
struct ANDconvolution
{
    long long poww(long long a, long long b, long long mod)
    {
        long long ans = 1;
        while (b > 0)
        {
            if (b & 1) ans = (ans * a) % mod;
            b >>= 1;
            a = (a * a) % mod;
        }
        return ans;
    }

    void ANDtransform(vector<long long> &vec, bool inverse = 0)
    {
        for(int len = 1; 2 * len <= vec.size(); len <<= 1)
        {
            for(int i = 0; i < vec.size(); i += 2 * len)
            {
                for(int j = 0; j < len; j++)
                {
                    long long u = vec[i + j];
                    long long v = vec[i + len + j];
                    if( !inverse )
                    {
                        vec[i + j] = v;
                        vec[i + len + j] = (u + v);//%mod;
                    }
                    else
                    {
                        vec[i + j] = (-u + v);//%mod;
                        vec[i + len + j] = u;
                    }
                }
            }
        }
    }
    //input: two vector denoting coefficient of a polynomial
    //output: a vector denoting their multiplication x^a*x^b = x^(a and b)
    vector<long long> multiply( vector<long long> v1, vector<long long>v2 )
    {
        int d = 1, dd = max( v1.size(), v2.size() );
        while(d<dd)
            d*=2;
        v1.resize(d, 0);
        v2.resize(d, 0);
        vector<long long>res(d, 0);
        ORtransform(v1, 0);
        ORtransform(v2, 0);
        for( int i = 0; i < d; i++ ) res[i] = v1[i]*v2[i];
        ORtransform(res, 1);
        return res;
    }
    //input: two vector denoting coefficient of a polynomial
    //output: a vector denoting (poly)^n
    vector<long long> multiply( vector<long long>v1, int n )
    {
        int d = 1, dd = v1.size();
        while(d<dd)
            d*=2;
        v1.resize(d, 0);
        vector<long long>res(d, 0);
        ORtransform(v1, 0);
        for( int i = 0; i < d; i++ ) res[i] = poww( v1[i], n, mod );
        ORtransform(res, 1);
        return res;
    }

};


///******************* XOR CONVOLUTION ************************************
struct XORConvolution
{
    void WHtransform( vector<long long> &P, bool inverse = 0 )
    {
        for (int len = 1; 2 * len <= P.size(); len <<= 1)
        {
            for(int i = 0; i < P.size(); i += 2 * len)
            {
                for (int j = 0; j < len; j++)
                {
                    long long u = P[i + j];
                    long long v = P[i + len + j];
                    ///do modulu here when needed
                    P[i + j] = u + v;
                    ///do modulu here when needed
                    P[i + len + j] = u - v;
                }
            }
        }

        if (inverse)
        {
            //long long inv = poww(P.size(), mod-2, mod);
            for (int i = 0; i < P.size(); i++)
                P[i] = (P[i]/P.size()) ; //in case whole operation is done on modulo
        }
    }
    ///polynimial*polynomial where x^a*x^b = x^(a xor b);
    vector<long long> multiply( vector<long long> v1, vector<long long> v2 )
    {
        int d = 1, deg = max( (int)v1.size(), (int)v2.size() );
        while(d<deg)
            d*=2;
        v1.resize(d, 0);
        v2.resize(d, 0);
        vector<long long>v(d, 0);
        WHtransform( v1, 0 );
        WHtransform( v2, 0 );
        ///do modulu here when needed
        for( int i = 0; i < v1.size(); i++ ) v[i] = v1[i]*v2[i];
        WHtransform(v, 1);
        return v;
    }
    ///bigmod: (a^b)%mod
    long long poww(long long a, long long b, long long mod)
    {
        long long ans = 1;
        while(b)
        {
            if (b & 1) ans = (ans * a) % mod;
            b >>= 1;
            a = (a * a) % mod;
        }
        return ans;
    }
    /// polynomial^n
    vector<long long> multiply( vector<long long> v1, int pow )
    {
        int d = 1, deg = (int)v1.size();
        while(d<deg)
            d*=2;
        v1.resize(d, 0);
        vector<long long>v(d, 0);
        WHtransform( v1, 0 );
        for( int i = 0; i < v1.size(); i++ ) v[i] = poww(v1[i], pow, mod);
        WHtransform(v, 1);
        return v;
    }
};



