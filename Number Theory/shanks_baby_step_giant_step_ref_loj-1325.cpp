#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;

#define intl        long long

/*
return x where a^x = b % mod
complexity sqrt(mod)*log(mod)
n = sqrt(mod) + 1;
a^(pn-q) = b % mod -> a^(pn) = b*(a^q) % mod
p = [1,n], q = [0,n]
f1(p) = a^(pn)%mod
f2(q) = b*(a^q)% mod
if for some p, q we have f1(p) = f2(q)
answer is p*n - q
*/

int baby_step_giant_step( int a, int b, int mod )
{
    tr1::unordered_map<int,int> mm;
    int sqrtmod = sqrt(mod+0.0)+1;
    intl bigstep = 1;
    for( int i = 1; i <= sqrtmod; i++ )
    {
        bigstep = (bigstep*a)%mod;
    }
    intl val = 1;
    for( int i = 1; i <= sqrtmod; i++ )
    {
        val = ( val*bigstep )%mod;
        if( mm.count(val) == 0 )
        {
            mm[val] = i;
        }
    }
    //cout << mm.size() << endl;
    val = b; // b from a^x = b (% mod)
    int ans = INT_MAX; //inf value
    for( int i = 0; i <= sqrtmod; i++ )
    {
        if( mm.count(val))
        {
            // modify mm[val]*sqrtmod - i, as needed
            ans = min( mm[val]*sqrtmod - i, ans );
        }
        val = (val*a)%mod;
    }
    return ans; //solution doesn't exist if ans is inf

}

int main()
{
    int t, caseno = 1;
    scanf("%d", &t);
    while(t--)
    {
        int a, b, mod = 100000007;
        scanf("%d %d", &a, &b);
        printf("Case %d: %d\n", caseno++, baby_step_giant_step(a,b,mod) );
    }
    return 0;
}