#include<bits/stdc++.h>
using namespace std;
typedef double ld ;

const ld pi=acos(-1.0);
const ld PI=acos(-1.0);
const ld eps=1e-10;
const ld EPS=1e-10;



struct PT
{

    ld x,y;
    PT() {}
    PT(ld x,
       ld y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
};
PT operator +(PT a,PT b)
{
    return PT(a.x+b.x,a.y+b.y);
}
PT operator -(PT a,PT b)
{
    return PT(a.x-b.x,a.y-b.y);
}
PT operator *(PT a,ld b)
{
    return PT(a.x*b,a.y*b);
}

PT operator /(PT a,
              ld b)
{
    return PT(a.x/b,a.y/b);
}
ld operator *(PT a,PT b) //dot
{
    return a.x*b.x+a.y*b.y;
}

ld operator ^(PT a,PT b) //cross
{
    return a.x*b.y-a.y*b.x;
}

int dcmp(ld x)
{
    if (fabs(x)<eps) return 0;
    return x<0 ? -1 : 1;
}

bool operator <(const PT &a,const PT &b)
{
    return make_pair(a.x,a.y)<make_pair(b.x,b.y);
}
bool operator==(const PT &a,const PT &b)
{
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y) == 0;
}
ld len(PT a)
{
    return sqrt(a*a);
}
ld len2(PT a)
{
    return (a*a);
}
ld dist(PT a, PT b)
{
    return sqrt((a-b)*(a-b));
}
ld dist2(PT a, PT b)
{
    return ((a-b)*(a-b));
}
inline ld sqr(ld a)
{
    return a*a;
}

PT RotateCCW90(PT p)
{
    return PT{-p.y,p.x};
}
PT RotateCW90(PT p)
{
    return PT{p.y,-p.x};
}

// t is angle in radian

PT RotateCCW(PT p, ld t)
{
    return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));
}


//intersection area of triangle((0,0), A, B) and circle with center cen, radius r
ld Tri_cross_Cir(PT A,PT B,PT cen,ld r)
{
    ld a,b,c,x,y,s=((A-cen)^(B-cen))*0.5;
    a=len(B-cen);
    b=len(A-cen);
    c=len(A-B);
    if(a<=r&&b<=r)return s;
    else if(a<r&&b>=r)
    {
        x=((A-B)*(cen-B)+sqrt(c*c*r*r-sqr((A-B)^(cen-B))))/c;
        return asin(s*(c-x)*2.0/c/b/r)*r*r*0.5+s*x/c;
    }
    else if(a>=r&&b<r)
    {
        y=((B-A)*(cen-A)+sqrt(c*c*r*r-sqr((B-A)^(cen-A))))/c;
        return asin(s*(c-y)*2.0/c/a/r)*r*r*0.5+s*y/c;
    }
    else
    {
        if(fabs(2.0*s)>=r*c||(B-A)*(cen-A)<=0||(A-B)*(cen-B)<=0)
        {
            if((A-cen)*(B-cen)<0)
            {
                if(((A-cen)^(B-cen))<0)return (-pi-asin(s*2.0/a/b))*r*r*0.5;
                else return (pi-asin(s*2.0/a/b))*r*r*0.5;
            }
            else return asin(s*2/a/b)*r*r*0.5;
        }
        else
        {
            x=((A-B)*(cen-B)+sqrt(c*c*r*r-sqr((A-B)^(cen-B))))/c;
            y=((B-A)*(cen-A)+sqrt(c*c*r*r-sqr((B-A)^(cen-A))))/c;
            return (asin(s*(1-x/c)*2/r/b)+asin(s*(1-y/c)*2/r/a))*r*r*0.5+s*((y+x)/c-1);
        }
    }
}

/*
pp[] is the list of vertices, cen is circle center, r is circle radius
send one segment of the polygon at a time consisting vertices A,B
*/
PT pp[10];
ld polygonCircleArea(PT cen, int n,
                     ld r)
{

    ld ans=0;
    for(int i=0; i<n; i++)ans+=(Tri_cross_Cir(pp[i], pp[i+1],cen,r));
    return fabs(ans);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d)
{
    return fabs((b-a)^(c-d)) < eps;
}

bool LinesCollinear(PT a, PT b, PT c, PT d)
{
    return LinesParallel(a, b, c, d)
           && fabs((a-b)^(a-c)) < eps
           && fabs((c-d)^(c-a)) < eps;
}

//intersection of line ab and cd
PT ComputeLineIntersection(PT a, PT b, PT c, PT d)
{
    b=b-a;
    d=c-d;
    c=c-a;
    assert((b*b) > EPS && (d*d) > EPS);
    return a + b*(c^d)/(b^d);
}

//projection of point p on line AB
PT GetLineProjection(PT p,PT A,PT B)
{
    PT v=B-A;
    return A+v*(v*(p-A))/(v*v);
}

//distance from point p to line AB
ld DistanceToLine(PT p,PT A,PT B)
{
    PT v1 = B-A, v2 = p-A;
    return fabs(v1^v2)/len(v1);
}

//checks whether segment AB and segment CD intersects
bool SegmentsIntersect(PT a, PT b, PT c, PT d)
{
    if (LinesCollinear(a, b, c, d))
    {
        if (dist2(a, c) < eps || dist2(a, d) < eps ||
                dist2(b, c) < eps || dist2(b, d) < eps) return true;
        if ((c-a)*(c-b) > 0 && (d-a)*(d-b) > 0 && (c-b)*(d-b) > 0)
            return false;
        return true;
    }
    if (((d-a)^(b-a))*((c-a)^(b-a)) > 0) return false;
    if (((a-c)^(d-c))*((b-c)^(d-c)) > 0) return false;
    return true;
}

// project point c onto line segment AB
PT ProjectPointSegment(PT a, PT b, PT c)
{

    ld r = (b-a)*(b-a);
    if (fabs(r) < EPS) return a;
    r = (c-a)*(b-a)/r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b-a)*r;
}

//determine if p is on segment ab
bool OnSegment(PT p,PT a,PT b)
{
    return dcmp((a-p)^(b-p)) == 0 && dcmp((a-p)*(b-p))<0;
}

//distance from point p to segment AB
ld DistanceToSegment(PT p,PT A,PT B)
{
    if (A==B) return len(p-A);
    PT v1 = B-A, v2 = p-A, v3 = p - B;
    if (dcmp(v1*v2)<0) return len(v2);
    else if (dcmp(v1*v3)>0 ) return len(v3);
    else return fabs(v1^v2) / len(v1);
}

/*
// compute distance between point (x,y,z) and plane ax+by+cz=d

ld DistancePointPlane(ld x,
                      ld y, ld z,
                      ld a, ld b,
                      ld c, ld d)
{
    return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}



// determine if line segment from a to b intersects with


// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<PT> &p, PT q)
{
    bool c = 0;
    for (int i = 0; i < p.size(); i++)
    {
        int j = (i+1)%p.size();
        if ((p[i].y <= q.y && q.y < p[j].y ||
                p[j].y <= q.y && q.y < p[i].y) &&
                q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
            c = !c;
    }
    return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<PT> &p, PT q)
{
    for (int i = 0; i < p.size(); i++)
        if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
            return true;
    return false;
}
*/


ld triArea2(PT A,PT B,PT C)
{
    return abs((B-A)^(C-A));
}

//Circle structure
struct CR
{
    PT c;

    ld r,x,y;
    CR(PT c,ld r):c(c),r(r),x(c.x),y(c.y) {}
    PT point(ld rad)
    {
        return PT(c.x+cos(rad)*r,c.y+sin(rad)*r);
    }
};

struct Line
{
    PT p, v;
    ld ang;
    Line() {}
    Line(PT p,PT v):p(p),v(v)
    {
        //Principal arc tangent of y/x, in the interval [-pi,+pi] radians
        ang=atan2(v.y,v.x);
    }
    //slope comparison
    bool operator<(const Line & L) const
    {
        return ang<L.ang;
    }
    PT point(ld t)
    {
        return p+v*t;
    }
};


int getLineCircleIntersection(Line L, CR cir, vector<PT> &sol)
{
    if ( dcmp(DistanceToLine(cir.c,L.p,L.p+L.v)-cir.r)==0)
    {
        PT A=GetLineProjection(cir.c,L.p,L.p+L.v);
        sol.push_back(A);
        return 1;
    }

    ld a = L.v.x, b = L.p.x - cir.c.x, c = L.v.y, d= L.p.y - cir.c.y;
    ld e = a*a+c*c, f = 2*(a*b + c*d), g = b*b+d*d-cir.r*cir.r;
    ld delta = f*f - 4*e*g;
    ld t1, t2;
    if (dcmp(delta)<0) return 0;
    else if (dcmp(delta)==0)
    {
        t1 = t2 = -f / (2*e);
        sol.push_back(L.point(t1));
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2*e);
    sol.push_back(L.point(t1));
    t2 = (-f + sqrt(delta)) / (2*e);
    sol.push_back(L.point(t2));
    return 2;
}


ld angle(PT v)
{
    return atan2(v.y,v.x);
}

int getCircleCircleIntersection(CR C1,CR C2, vector<PT>& sol)
{
    ld d = len(C1.c-C2.c);
    if (dcmp(d)==0)
    {
        if (dcmp(C1.r - C2.r)==0) return -1; //same circle
        return 0; //concentric circle
    }
    if (dcmp(C1.r+C2.r-d)<0) return 0; //no intersection, outside
    if (dcmp(fabs(C1.r-C2.r)-d)>0) return 0; //no intersection, inside

    ld a = angle(C2.c-C1.c);
    ld da = acos((C1.r*C1.r+d*d - C2.r*C2.r)/ (2*C1.r*d));
    PT p1 = C1.point(a-da), p2 = C1.point(a+da);
    sol.push_back(p1);
    if (p1==p2) return 1;
    sol.push_back(p2);
    return 2;
}

//tangent from p to circle c
//returns direction vector from p to c
int getTangents(PT p,CR c, vector<PT> &sol)
{
    PT u= c.c-p;
    ld dist = len(u);
    if (dist<c.r) return 0;
    else if (dcmp(dist-c.r)==0)
    {
        sol.push_back(RotateCCW(u,PI/2));
        return 1;
    }
    else
    {
        ld ang = asin(c.r / dist);
        sol.push_back(RotateCCW(u,-ang));
        sol.push_back(RotateCCW(u,ang));
        return 2;
    }
}


//tangent from p to circle c
//returns points on circle that touches the tangent
int getTangentsPoint(PT p,CR c, vector<PT> &point)
{
    PT u= c.c-p;
    ld dist = len(u);
    if (dist<c.r) return 0;
    else if (dcmp(dist-c.r)==0)
    {
        point.push_back(p);
        return 1;
    }
    else
    {
        PT v;
        ld ang = asin(c.r / dist);
        v = RotateCCW(u,-ang);
        point.push_back(GetLineProjection(c.c,p,p+v));
        v = RotateCCW(u, ang);
        point.push_back(GetLineProjection(c.c,p,p+v));
        return 2;
    }
}

//common tangent of two circle A and B
//return the point on circles the tangent touches
//ai-bi is a common tangent

int getTangents(CR A,CR B, vector<PT> &a, vector<PT> &b)
{
    int cnt=0;
    if (A.r<B.r)
    {
        swap(A,B),
        swap(a,b);
    }
    ld d2 = (A.c.x-B.c.x)*(A.c.x-B.c.x) + (A.c.y-B.c.y)*(A.c.y-B.c.y);
    ld rdiff = A.r-B.r;
    ld rsum = A.r+B.r;
    if (d2 < rdiff*rdiff) return 0;
    ld base = atan2(B.y-A.y,B.x-A.x);
    if (d2 == 0 && A.r == B.r) return -1;
    if (dcmp(d2-rdiff*rdiff)==0)
    {
        a.push_back(A.point(base));
        b.push_back(B.point(base));
        return 1;
    }
    ld ang = acos((A.r-B.r)/sqrt(d2));
    a.push_back(A.point(base+ang));
    b.push_back(B.point(base+ang));
    a.push_back(A.point(base-ang));
    b.push_back(B.point(base-ang));
    if (dcmp(d2-rsum*rsum))
    {
        a.push_back(A.point(base));
        b.push_back(B.point(base+PI));
    }
    else if (dcmp(d2-rsum*rsum)==1)
    {
        ld ang = acos((A.r+B.r)/sqrt(d2));
        a.push_back(A.point(base+ang));
        b.push_back(B.point(PI+base+ang));
        a.push_back(A.point(base-ang));
        b.push_back(B.point(PI+base-ang));
    }
    return a.size();
}

// pori_britto

CR CircumscribedCircle(PT p1,PT p2,PT p3)
{
    ld Bx = p2.x-p1.x, By= p2.y-p1.y;
    ld Cx = p3.x-p1.x, Cy= p3.y-p1.y;

    ld D = 2*(Bx*Cy-By*Cx);
    ld cx = (Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D + p1.x;

    ld cy = (Bx*(Cx*Cx+Cy*Cy)-Cx*(Bx*Bx+By*By))/D + p1.y;
    PT p =PT(cx,cy);
    return CR(p,len(p1-p));
}

// ontor_britto

CR InscribedCircle(PT p1,PT p2,PT p3)
{
    ld a = len(p2-p3);

    ld b = len(p3-p1);
    ld c = len(p1-p2);
    PT p = (p1*a+p2*b+p3*c)/(a+b+c);
    return CR(p,DistanceToLine(p,p1,p2));
}


ld degToRad(ld deg)
{
    return deg/180*PI;
}

ld radToPositive(
                 ld rad)
{
    if (dcmp(rad)<0) rad=ceil(-rad/PI)*PI+rad;
    if (dcmp(rad-PI)>=0) rad-=floor(rad/PI)*PI;
    return rad;
}

ld radToDeg(ld rad)
{
    return rad*180/PI;
}

PT normalUnit(PT A)
{
    ld L = len(A);
    return PT(-A.y/L, A.x/L);
}

Line LineTranslation(Line l, PT v)
{
    l.p = l.p+v;
    return l;
}
//sol contains the center of these circles
void CircleThroughAPointAndTangentToALineWithRadius(PT p,Line l,
                                                    ld r,vector<PT>& sol)
{
    PT e = normalUnit(l.v);
    Line l1=LineTranslation(l,e*r),l2=LineTranslation(l,e*(-r));
    getLineCircleIntersection(l1,CR(p,r), sol);
    getLineCircleIntersection(l2,CR(p,r), sol);
}

//sol contains the center of these circles
void CircleTangentToTwoLinesWithRadius(Line l1,Line l2,
                                       ld r,vector<PT>& sol)
{
    PT e1 = normalUnit(l1.v), e2 = normalUnit(l2.v);
    Line L1[2]= {LineTranslation(l1,e1*r),LineTranslation(l1,e1*(-r))},
                L2[2]= {LineTranslation(l2,e2*r),LineTranslation(l2,e2*(-r))};
    for( int i = 0; i < 2; i++ )
    {
        for( int j = 0; j < 2; j++ )
        {
            sol.push_back(ComputeLineIntersection(L1[i].p,L1[i].v,L2[j].p,L2[j].v));
        }
    }
}


//sol contains the center of these circles
void CircleTangentToTwoDisjointCirclesWithRadius(CR c1, CR c2,
                                                 ld r, vector<PT>& sol)
{
    c1.r += r;
    c2.r += r;
    getCircleCircleIntersection(c1,c2,sol);
}

//determine if point p is on/in/out of convex / concave polygon
int isPointInPolygon(PT p, vector<PT> &poly)
{
    int wn=0;
    int n=poly.size();
    for(int i = 0; i < n; i++)
    {
        if (OnSegment(p,poly[i],poly[(i+1)%n])) return -1; //on edge
        int k=dcmp((poly[(i+1)%n]-poly[i])^(p-poly[i]));
        int d1 = dcmp(poly[i].y-p.y);
        int d2 = dcmp(poly[(i+1)%n].y-p.y);
        if ( k > 0 && d1 <= 0 && d2 > 0 ) wn++;
        if ( k < 0 && d2 <= 0 && d1 > 0 ) wn--;
    }
    if (wn!=0) return 1; //inside
    return 0; //outside
}

/// triangle vertex a , b , c ; Target T // returns 1 if Point is on or inside the triangle
int PointsInTriangle (PT a , PT b , PT c , PT T) {

    ld A1 = triArea2(a,b,T) , A2 = triArea2(b,c,T) , A3 = triArea2(c,a,T) , A = triArea2(a,b,c) ;
    if ( dcmp(A- (A1 + A2 + A3)) == 0) {
        return 1 ;
    }
    return 0 ;
}
/// returns 1 if CCW or collinear , returns 0 if CW
bool CCW(PT a, PT b, PT c) {
    long long area = a.x*b.y + b.x*c.y + c.x*a.y - b.x*a.y - c.x*b.y - a.x*c.y ;
    if( area >= 0.0 ) return 1 ;
    return 0 ;
}
/// Points in Polygon must be in CCW and no three collinear points
/// if collinear exits compute its convex to remove them
int PointsInConvexPolygon (vector <PT> &P , PT T) {
    if (P.size() < 3) return 0 ; /// not a convex polygon
    int lo = 1 , hi = P.size() - 1 ;
    while (hi-lo > 1) {
        int mid = (hi+lo)/2 ;
        if (CCW(P[0],P[mid],T)) {
            lo = mid ;
        }
        else {
            hi = mid ;
        }
    }
     // Add three ifs if the point is strictly inside needed
    /*if (lo == 1 and Area(P[0],P[lo],T) == 0) {
        return 0 ;
    }
    if (hi == lo + 1 and Area(P[lo],P[hi],T) == 0) {
        return 0 ;
    }
    if (hi == P.size() - 1 and Area(P[0],P[hi],T) == 0) {
        return 0 ;
    }*/
    return PointsInTriangle(P[0],P[lo],P[hi],T) ;
}


//input p[]: given points in plane
//output sol[]: convex hull of p[]
PT ch[101000];
void ConvexHull( vector<PT> &p, vector<PT> &sol)
{
    sort(p.begin(),p.end());
    int m = 0;
    int n = p.size();
    for( int i = 0; i < n; i++ )
    {
        while(m>1 && ((ch[m-1]-ch[m-2])^(p[i]-ch[m-2]))<=0) m--;
        ch[m++]=p[i];
    }
    int k = m;
    for( int i = n-2; i >= 0; i-- )
    {
        while(m>k && ((ch[m-1]-ch[m-2])^(p[i]-ch[m-2])) <= 0) m--;
        ch[m++] = p[i];
    }
    if ( n > 1 ) m--;
    for( int i = 0; i < m; i++ ) sol.push_back(ch[i]);
}

//input: polygon poly[], line AB(point representation)
//output: intersecting points of AB and polygon and upper/lower
//portion of AB on polygon
vector<PT> CutPolygon(vector<PT> &poly,PT A,PT B)
{
    vector<PT> newpoly;
    int n=poly.size();
    for( int i = 0; i < n; i++ )
    {
        PT C = poly[i];
        PT D = poly[(i+1)%n];
        if (dcmp((B-A)^(C-A))>=0)  newpoly.push_back(C);
        if (dcmp((B-A)^(C-D)))
        {
            PT ip = ComputeLineIntersection(A,B-A,C,D-C);
            if (OnSegment(ip,C,D)) newpoly.push_back(ip);
        }
    }
    return newpoly;
}

ld PolygonArea(vector<PT> &p)
{

    ld area=0;
    int n=p.size();
    for( int i = 1; i <= n-2; i++ )
        area += abs((p[i]-p[0])^(p[i+1]-p[0]));
    return area/2.0;
}

//is the point p on left of line L?
bool OnLeft(Line L,PT p)
{
    return ((L.v)^(p-L.p)) > 0;
}

//intersection of line a and b
PT GetIntersection(Line a,Line b)
{
    if( dcmp((a.v)^(b.v)) == 0 ) return PT(1e10, 1e10);
    PT u = a.p-b.p;
    ld t = ((b.v)^(u))/((a.v)^(b.v));
    return a.p + a.v*t;
}

//diameter of a convex polygon p
ld rotating_calipers(vector<PT> p)
{
    int q = 1, n = p.size();

    ld ans = 0;
    for( int i = 0; i < n; i++ )
    {
        while(triArea2(p[i],p[(i+1)%n],p[(q+1)%n]) > triArea2(p[i],p[(i+1)%n],p[q] ))
            q=(q+1)%n;
        ans = max( ans, (
                         ld)max(len(p[i]- p[q]), len(p[(i+1)%n] -p[q] ) ) );
    }
    return ans;
}
//minimum area rectangle for convex polygon

ld rec_rotating_calipers(PT *p,int n)
{
    int q=1;
    ld ans1=1e15,ans2=1e15;
    int l=0,r=0;
    for( int i = 0; i < n; i++ )
    {
        while(dcmp(triArea2(p[i],p[(i+1)%n],p[(q+1)%n])-triArea2(p[i],p[(i+1)%n],p[q] )) >0)
            q=(q+1)%n;
        while (dcmp((p[(i+1)%n]-p[i])*(p[(r+1)%n]-p[r]))>0 )
            r=(r+1)%n;
        if (!i) l = q;
        while (dcmp((p[(i+1)%n]-p[i])*(p[(l+1)%n]-p[l]))<0 )
            l=(l+1)%n;

        ld d = len(p[(i+1)%n]-p[i]);

        ld h = triArea2(p[i],p[(i+1)%n],p[q] )/d;
        ld w =(((p[(i+1)%n]-p[i])*(p[r]-p[i]))-((p[(i+1)%n]-p[i])*(p[l]-p[i])))/d;
        ans1 = min(ans1, 2*(h+w)), ans2 = min(ans2,h*w);
    }
    printf("%.2lf %.2lf\n",ans2,ans1);
}

/*tangent lines to a convex polygon from a point outside*/

#define CW 		-1
#define ACW	 	 1
#define pii pair<int, int>
#define xx first
#define yy second
#define LL long long

int direction(pii st, pii ed, pii q){
	LL xp = (LL) (ed.xx - st.xx) * (q.yy - ed.yy) - (LL) (ed.yy - st.yy) * (q.xx - ed.xx);
	if(!xp) return 0;
	if(xp > 0) return ACW;
	return CW;
}

bool isGood(pii u, pii v, pii Q, int dir){
    return (direction(Q, u, v) != -dir);
}

pii better(pii u, pii v, pii Q, int dir){
    if(direction(Q, u, v) == dir) return u;
    return v;
}

pii tangents(vector<pii> &hull, pii Q, int dir, int lo, int hi){
    int mid;

    while(hi - lo + 1 > 2){
        mid = (lo + hi)/2;
        bool pvs = isGood(hull[mid], hull[mid - 1], Q, dir);
        bool nxt = isGood(hull[mid], hull[mid + 1], Q, dir);

        if(pvs && nxt) return hull[mid];
        if(!(pvs || nxt)){
            pii p1 = tangents(hull, Q, dir, mid+1, hi);
            pii p2 = tangents(hull, Q, dir, lo, mid - 1);
            return better(p1, p2, Q, dir);
        }

        if(!pvs){
            if(direction(Q, hull[mid], hull[lo]) == dir)  hi = mid - 1;
            else if(better(hull[lo], hull[hi], Q, dir) == hull[lo]) hi = mid - 1;
            else lo = mid + 1;
        }
        if(!nxt){
            if(direction(Q, hull[mid], hull[lo]) == dir)  lo = mid + 1;
            else if(better(hull[lo], hull[hi], Q, dir) == hull[lo]) hi = mid - 1;
            else lo = mid + 1;
        }
    }

    pii ret = hull[lo];
    for(int i = lo + 1; i <= hi; i++) ret = better(ret, hull[i], Q, dir);
    return ret;
}

/// [ACW, CW] Tangent
pair< pii, pii> get_tangents(vector<pii> &polygon, pii Q){

    pii acw_tan = tangents(polygon, Q, ACW, 0, (int) polygon.size() - 1);
    pii cw_tan = tangents(polygon, Q, CW, 0, (int) polygon.size() - 1);



    return make_pair(acw_tan, cw_tan);
}

/****finish point to polygon tangent***/


ld angle( pii a, pii b, pii c )
{
    ld d = triArea2( PT(a.xx,a.yy), PT(b.xx,b.yy), PT(c.xx,c.yy) );
    d /= dist( PT(a.xx,a.yy), PT(b.xx,b.yy) );
    d /= dist( PT(a.xx,a.yy), PT(c.xx,c.yy) );
    d = min((ld)1.00, d);
    d = max((ld)0.00, d);
    d = asin(d);
    d *= (180/PI);
    return d;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<CR>cr;
    vector< pair<int,int> >vec;
    ld x, y;
    for( int i = 0; i < n; i++ )
    {
        cin >> x >> y;
        int a = round(x*100.0), b = round(y*100.0);
        vec.push_back( {a,b} );
        cr.push_back( CR(PT(x,y),1.0) );
    }
    int tot = 1;
    for( int i = 1; i < n; i++ )
    {
        if( vec[i].first == vec[i-1].first && vec[i].second == vec[i-1].second )
            tot++;
    }
    if( tot == n )
    {
        cout << n << endl;
        return 0;
    }
    int ans = 1;
    for( int i = 0; i < n; i++ )
    {
        for( int j  = i+1; j < n; j++ )
        {
            if( vec[i].first == vec[j].first && vec[i].second == vec[j].second )
                continue;
            vector<PT>va, vb;
            getTangents( cr[i], cr[j], va, vb );
            vector<Line>vl;
            for( int p = 0; p < va.size(); p++ )
            {
                Line l;
                if( dcmp( va[p].x - vb[p].x ) == 0 && dcmp( va[p].y - vb[p].y ) == 0 )
                {
                    l = Line( va[i], RotateCW90( cr[i].c - cr[j].c ) );
                }
                else
                    l = Line(va[p], vb[p] - va[p]);
              //  cout << i << " " << j << ": " << l.p.x << " " << l.p.y << ", " << l.v.x << " " << l.v.y << endl;
                int tot = 0;
                for( int k  = 0; k < n; k++ )
                {
                    if (k==i or k==j) {
                        tot++;
                        continue ;
                    }
                    vector<PT>t;
                    int d = getLineCircleIntersection(l, cr[k], t);
                    if( d > 0 ) tot++;
                }
                ans = max(ans, tot);
            }

        }
    }
    cout << ans << endl;

    return 0;
}
