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
    //filein;
    int row, col;
    cin >> row >> col;
    int ara[row][col], rowsum[row][col];
    for( int i = 0; i < row; i++ )
    {
        for( int j = 0; j < col; j++ )
        {
            cin >> ara[i][j];
            if( j > 0 )
                rowsum[i][j] = rowsum[i][j-1] + ara[i][j];
            else
                rowsum[i][j] = ara[i][j];
        }
    }
    int ans = -1e9, sum;
    for( int i = 0; i < col; i++ )
    {
        for( int j = i; j < col; j++ ) /// sub matrix of size x*(j-i+1)
        {
            sum = 0;
            for( int k = 0; k < row; k++ ) /// 1D Kadane
            {
                if( i > 0 ) sum += rowsum[k][j] - rowsum[k][i-1];
                else sum += rowsum[k][j];
                ans = max(ans, sum);
                if(sum < 0)
                    sum = 0;
            }
        }
    }

    cout << ans << endl;


    return 0;
}




