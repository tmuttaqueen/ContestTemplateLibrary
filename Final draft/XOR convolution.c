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
