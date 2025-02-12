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
        ANDtransform(v1, 0);
        ANDtransform(v2, 0);
        for( int i = 0; i < d; i++ ) res[i] = v1[i]*v2[i];
        ANDtransform(res, 1);
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
        ANDtransform(v1, 0);
        for( int i = 0; i < d; i++ ) res[i] = poww( v1[i], n, mod );
        ANDtransform(res, 1);
        return res;
    }

};
