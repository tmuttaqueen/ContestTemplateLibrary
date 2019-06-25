#include <bits/stdc++.h>

using namespace std;

int samebit( int a )
{
    int c = a&(-a);
    int r = a + c;
    return (((r^a)>>2)/c)|r;
}

int main()
{
    int a = 3;
    cout << samebit(a) << endl;
}
