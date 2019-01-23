///Z-ALGORITHM O(n)
//calculateZ takes a string and an array as an input and returns Z value

void calculateZ( string &s, int zval[] )
{
    int len = s.length();
    int left = 0, right = 0;
    zval[0] = 0;
    for( int k = 1; k < len; k++ )
    {
        if( k > right )
        {
            left = right = k;
            while( right < len && s[right-left] == s[right] )
            {
                right++;
            }
            zval[k] = right - left;
            right--;
        }
        else
        {
            if( k + zval[k-left] < right )
            {
                zval[k] = zval[k-left];
            }
            else
            {
                left = k;
                while( right < len && s[right-left] == s[right] )
                {
                    right++;
                }
                zval[k] = right - left;
                right--;
            }
        }
    }
}
