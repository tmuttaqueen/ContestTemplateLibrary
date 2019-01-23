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

int main()
{
    ios::sync_with_stdio(false);
    filein;
    int n;
    cin >> n ;
    int backtrack[n+5];
    pii ara[n+5];
    set<pii>ss;
    set<pii>::iterator it;

    for( int i = 0; i < n; i++ )
    {
        cin >> ara[i].xx;
        ara[i].yy = i;
    }

    int ans = -1, index;
    for( int i = 0; i < n; i++ )
    {

        ss.insert(ara[i]);
        it = ss.find(ara[i]);

        if( it != ss.begin()  )
        {
            it--;
            backtrack[i] = (*it).yy;
            it++;
        }
        else
        {
            backtrack[i] = -1;
        }
        it++;
        if( it != ss.end() )
        {
            ss.erase(it);
        }
        if( (int)ss.size() > ans )
            index = i;
        ans = max( ans, (int)ss.size() );
    }

    cout <<  ans << endl;

    while( index != -1 )
    {
        cout << ara[index].xx << " ";
        index = backtrack[index];
    }

    return 0;
}




