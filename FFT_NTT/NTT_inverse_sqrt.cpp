#include <iostream>
#include <cstdio>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long s64;

const int Mod = 663224321;//998244353;
const int Mod_G = 3;

const int MaxCN = 100000;
const int MaxS = 100000;

struct modint
{
    int a;

    modint() {}
    modint(int _a)
    {
        a = _a % Mod;
        if (a < 0)
            a += Mod;
    }
    modint(s64 _a)
    {
        a = _a % Mod;
        if (a < 0)
            a += Mod;
    }

    inline modint operator-() const
    {
        return -a;
    }
    inline modint inv() const
    {
        int x1 = 1, x2 = 0, x3 = Mod;
        int y1 = 0, y2 = 1, y3 = a;
        while (y3 != 1)
        {
            int k = x3 / y3;
            x1 -= y1 * k, x2 -= y2 * k, x3 -= y3 * k;
            swap(x1, y1), swap(x2, y2), swap(x3, y3);
        }
        return y2 >= 0 ? y2 : y2 + Mod;
    }

    friend inline modint operator+(const modint &lhs, const modint &rhs)
    {
        return lhs.a + rhs.a;
    }
    friend inline modint operator-(const modint &lhs, const modint &rhs)
    {
        return lhs.a - rhs.a;
    }
    friend inline modint operator*(const modint &lhs, const modint &rhs)
    {
        return (s64)lhs.a * rhs.a;
    }
    friend inline modint operator/(const modint &lhs, const modint &rhs)
    {
        return lhs * rhs.inv();
    }

    inline modint div2() const
    {
        return (s64)a * ((Mod + 1) / 2);
    }
};

inline modint modpow(const modint &a, const int &n)
{
    modint res = 1;
    modint t = a;
    for (int i = n; i > 0; i >>= 1)
    {
        if (i & 1)
            res = res * t;
        t = t * t;
    }
    return res;
}

const int MaxN = 131072;
const int MaxTN = MaxN * 2;

modint prePowG[MaxTN];

void fft(int n, modint *a, int step, modint *out)
{
    if (n == 1)
    {
        out[0] = a[0];
        return;
    }
    int m = n / 2;
    fft(m, a, step + 1, out);
    fft(m, a + (1 << step), step + 1, out + m);
    for (int i = 0; i < m; i++)
    {
        modint e = out[i], o = out[i + m] * prePowG[i << step];
        out[i] = e + o;
        out[i + m] = e - o;
    }
}

void poly_mulTo(int n, modint *f, modint *g)
{
    int tn = n * 2;
    static modint tf[MaxTN], tg[MaxTN];
    copy(f, f + n, tf), fill(tf + n, tf + tn, modint(0));
    copy(g, g + n, tg), fill(tg + n, tg + tn, modint(0));

    modint rg = modpow(Mod_G, (Mod - 1) / tn);
    prePowG[0] = 1;
    for (int i = 1; i < tn; i++)
        prePowG[i] = prePowG[i - 1] * rg;

    static modint dftF[MaxTN], dftG[MaxTN];
    fft(tn, tf, 0, dftF);
    fft(tn, tg, 0, dftG);

    for (int i = 0; i < tn; i++)
        dftF[i] = dftF[i] * dftG[i];

    reverse(prePowG + 1, prePowG + tn);
    fft(tn, dftF, 0, tf);
    reverse(prePowG + 1, prePowG + tn);

    modint revTN = modint(tn).inv();
    for (int i = 0; i < n; i++)
        f[i] = tf[i] * revTN;
}

//size as n = 2^k, f is the function, r is the result
void poly_inv(int n, modint *f, modint *r)
{
    fill(r, r + n, modint(0));
    r[0] = 1;
    for (int m = 2; m <= n; m <<= 1)
    {
        int h = m / 2;
        static modint nr[MaxN];
        copy(f, f + m, nr);
        poly_mulTo(m, nr, r);
        fill(nr, nr + h, modint(0));
        for (int i = h; i < m; i++)
            nr[i] = -nr[i];
        poly_mulTo(m, nr, r);
        copy(nr + h, nr + m, r + h);
    }
}

//size as n = 2^k, f is the function, s is the result
void poly_sqrt(int n, modint *f, modint *s)
{
    fill(s, s + n, modint(0));
    s[0] = 1;

    static modint rs[MaxN];
    fill(rs, rs + n, modint(0));
    rs[0] = 1;
    for (int m = 2; m <= n; m <<= 1)
    {
        int h = m / 2;
        static modint nrs[MaxN];
        copy(s, s + h, nrs), fill(nrs + h, nrs + m, modint(0));
        poly_mulTo(m, nrs, rs);
        fill(nrs, nrs + h, modint(0));
        for (int i = h; i < m; i++)
            nrs[i] = -nrs[i];
        poly_mulTo(m, nrs, rs);
        copy(rs, rs + h, nrs);
        poly_mulTo(m, nrs, f);
        for (int i = h; i < m; i++)
            s[i] = nrs[i].div2();
        copy(s, s + m, nrs);
        poly_mulTo(m, nrs, rs);
        fill(nrs, nrs + h, modint(0));
        for (int i = h; i < m; i++)
            nrs[i] = -nrs[i];
        poly_mulTo(m, nrs, rs);
        copy(nrs + h, nrs + m, rs + h);
    }
}

long long binary_expo( long long a, long long b, long long mod )
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

//calculates 2/( 1 + sqrt(1 - 4f(x)) )
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int c_n, s;
    static int c[MaxCN];

    cin >> c_n >> s;
    for (int i = 0; i < c_n; i++)
        scanf("%d", &c[i]);

    int n = 1;
    while (n < s + 1)
        n <<= 1;

    static modint fD[MaxN];
    fD[0] = 1;
    for (int i = 0; i < c_n; i++)
        if (c[i] <= s)
            fD[c[i]] = -4;

    static modint fB[MaxN];
    poly_sqrt(n, fD, fB);

    fB[0] = fB[0] + 1;

    for (int i = 0; i < n; i++)
        fB[i] = fB[i].div2();

    static modint f[MaxN];
    poly_inv(n, fB, f);

    for (int i = 1; i <= s; i++)
        printf("%d\n", f[i].a);

    return 0;
}
