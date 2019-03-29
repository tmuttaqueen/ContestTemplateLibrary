#include<bits/stdc++.h>

using namespace std;


class ahoCorasic
{
public:
    int sigma , maxSize , curSize ;
    int to[150][150] , link[150] ;
    int mask[155] ;
    //0 based trie, 0 is the root, curSize denote the number of states now, 0 ,1,....,curSize-1
    //endedHere[i] = the strings ended in the i'th node of trie
    //to[i][j] = 0, if there is no such state, otherwise it denotes the state to go from i, after adding j'th symbol
    //g[i][....] contains the node whose suffix link is to i, that means link[ g[i][j] ] = i
    //sigma = size of alphabet , link[i] points to the max suffix of string ended at i'th node

    ahoCorasic( int _sigma , int _maxSize )
    {
        sigma = _sigma ;
        maxSize = _maxSize ;
        for(int i=0 ; i<maxSize+2 ; i++)
        {
            for(int j=0 ; j<sigma ; j++) to[i][j] = 0 ;
        }
        curSize = 1 ;
        //   printf("Initialization\n") ;
    }
    void addString(string const& S ,int idx )
    {
      //  cout<<S<<endl ;
        int cur = 0 ;
        for( auto ch : S )
        {
            if( to[cur][ ch-'0' ]==0 ) to[cur][ch-'0'] = curSize++ ;
            cur = to[cur][ ch-'0' ] ;
        }
        mask[cur] |= (1<<idx) ;
//        printf("%d\n",cur) ;
        // now the value of cur is where the string ended , you may do whatever you want
    }
    void findSuffixLink()
    {
        int i ;
        queue < int > q ;

        for(i=0 ; i<sigma ; i++)
        {
            if( to[0][i] != 0 )
            {
                link[ to[0][i] ] = 0 ;
                q.push(to[0][i]) ;
                g[0].pb( to[0][i] ) ;
            }
        }

        while(!q.empty())
        {
            int state = q.front() ;
            q.pop() ;

            for(int ch = 0 ; ch<sigma ; ch++)
            {
                if( to[state][ch]!=0 )
                {
                    int failure = link[state] ;
                    while( failure != 0 && to[failure][ch]==0 ) failure = link[failure] ;
                    link[ to[state][ch] ] = to[ failure ][ch] ;
                    g[ to[ failure ][ch] ].pb( to[state][ch] ) ;
                    mask[ to[state][ch] ] |= mask[ to[ failure ][ch] ] ;
                    q.push( to[state][ch] ) ;
                }
            }
        }
    }
    int findNextState( int state , int input)
    {
        while( state!=0 && to[ state ][input]==0 ) state = link[state] ;
        return to[ state ][input] ;
    }
};
