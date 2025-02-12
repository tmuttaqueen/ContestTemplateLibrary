
/*
    -------------------------------> SUFFIX ARRAY + LONGEST COMMON PREFIX (LCP) <-------------------------------------------
    suffix array in O(nlogn)
    lcp from suffix_array via kasai algo in O(n)
*/


#include <bits/stdc++.h>
using namespace std ;

namespace SA
{
const int N = int(1e7)+10;
int cmp(int *r,int a,int b,int l)
{
    return (r[a]==r[b]) && (r[a+l]==r[b+l]);
}
int wa[N],wb[N],wws[N],wv[N];
int rnk[N],height[N];

void DA(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++) wws[i]=0;
    for(i=0; i<n; i++) wws[x[i]=r[i]]++;
    for(i=1; i<m; i++) wws[i]+=wws[i-1];
    for(i=n-1; i>=0; i--) sa[--wws[x[i]]]=i;
    for(j=1,p=1; p<n; j*=2,m=p)
    {
        for(p=0,i=n-j; i<n; i++) y[p++]=i;
        for(i=0; i<n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0; i<n; i++) wv[i]=x[y[i]];
        for(i=0; i<m; i++) wws[i]=0;
        for(i=0; i<n; i++) wws[wv[i]]++;
        for(i=1; i<m; i++) wws[i]+=wws[i-1];
        for(i=n-1; i>=0; i--) sa[--wws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i<n; i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}
void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1; i<=n; i++) rnk[sa[i]]=i;
    for(i=0; i<n; height[rnk[i++]]=k)
        for(k?k--:0,j=sa[rnk[i]-1]; r[i+k]==r[j+k]; k++);
}

int sa[N],data[N],n,p,q;


void CreateSA(char *A, int saa[], int lcp[])
{
    n = strlen(A) ;
    for (int i = 0 ; i < n ; i++)
    {
        data[i] = A[i] ;
    }
    DA(data,sa,n+1,128);
    calheight(data,sa,n);
    ///so far sa and height contains 1 based SA
    ///transforming it into 0-based SA
    for (int i = 0 ; i < n ; i++)
    {
        saa[i] = sa[i+1] ;
        lcp[i] = height[i+1] ;
        //cout << saa[i] << " " << lcp[i] << endl;
    }
}
}

const int n = 1e7+3;
char str[n];
int sa[n], lcp[n];

int main ()
{
    scanf ("%s", str) ;
    SA::CreateSA(str, sa, lcp);
    return 0;
}

