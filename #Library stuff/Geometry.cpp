#include <vector>
#include <algorithm>
#include <cstdlib>
#include <complex>
#include <iostream>

using namespace std;

typedef complex<long double> point;
typedef pair<point, point> segment;
#define F first
#define S second
#define X real()
#define Y imag()
#define vec(a, b) ((b)-(a))
#define polar(r, t) ((r)*exp(point(0,(t))))
#define angle(v) (atan2((v).Y,(v).X))
#define length(v) ((ld)hypot((v).Y,(v).X))
#define lengthSqr(v) (dot(v,v))
#define dot(a, b) ((conj(a)*(b)).real())
#define cross(a, b) ((conj(a)*(b)).imag())
#define rotate(v, t) (polar(v,t))
#define rotateabout(v, t, a)  (rotate(vec(a,v),t)+(a))
#define reflect(p, m) ((conj((p)/(m)))*(m))
#define normalize(p) ((p)/length(p))
#define same(a, b) (lengthSqr(vec(a,b))<EPS)
#define mid(a, b) (((a)+(b))/point(2,0))
#define perp(a) (point(-(a).Y,(a).X))
#define colliner pointOnLine

struct line {
    ll a, b, c;

    line(ll x1, ll y1, ll x2, ll y2) {
        a = y2 - y1;
        b = x1 - x2;
        c = -a * x1 - b * y1;
        auto g = abs(__gcd(a, __gcd(b, c)));
        if (a < 0 || (a == 0 && b < 0)) g *= -1;
        a /= g;
        b /= g;
        c /= g;
    }

    bool operator<(const line &q) const {
        if (a != q.a) return a < q.a;
        else if (b != q.b) return b < q.b;
        else return c < q.c;
    }
    bool operator==(const line &q) const {
        return a == q.a && b == q.b && c == q.c;
    }
};

enum STATE {
    IN, OUT, BOUNDRY
};

bool lineLineIntersect(const point& a, const point& b, const point& p, const point& q, point& ret) {
    //handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)
    double d1 = cross(vec(a, p), vec(a, b));
    double d2 = cross(vec(a, q), vec(a, b));
    ret = (d1 * q - d2 * p) / (d1 - d2);
    if (fabs(d1 - d2) > EPS) return 1;
    return 0;
}

bool pointOnLine(const point &a, const point &b, const point &p) {
    // degenerate case: line is a point
    return fabs(cross(vec(a, b), vec(a, p))) < EPS;
}

bool pointOnRay(const point &a, const point &b, const point &p) {
    //IMP NOTE: a,b,p must be collinear
    return dot(vec(a, p), vec(a, b)) > -EPS;
}

bool pointOnSegment(const point &a, const point &b, const point &p) {
    if (!colliner(a, b, p)) return 0;
    return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}

long double pointLineDist(const point &a, const point &b, const point &p) {
    // handle degenrate case: (a,b) is point

    return fabs(cross(vec(a, b), vec(a, p)) / length(vec(a, b)));
}

long double pointSegmentDist(const point &a, const point &b, const point &p) {
    if (dot(vec(a, b), vec(a, p)) < EPS)
        return length(vec(a, p));
    if (dot(vec(b, a), vec(b, p)) < EPS)
        return length(vec(b, p));
    return pointLineDist(a, b, p);
}

int segmentLatticePointsCount(int x1, int y1, int x2, int y2) {
    return abs(__gcd(x1 - x2, y1 - y2)) + 1;
}

long double triangleAreaBH(long double b, long double h) {
    return b * h / 2;
}

long double triangleArea2sidesAngle(long double a, long double b, long double t) {
    return fabs(a * b * sin(t) / 2);
}

long double triangleArea2anglesSide(long double t1, long double t2,
                                    long double s) {
    return fabs(s * s * sin(t1) * sin(t2) / (2 * sin(t1 + t2)));
}

long double triangleArea3sides(long double a, long double b, long double c) {
    long double s((a + b + c) / 2);
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

long double triangleArea3points(const point &a, const point &b, const point &c) {
    return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2;
}

//count interior
int picksTheorm(int a, int b) {
    return a - b / 2 + 1;
}

//get angle opposite to side a
long double cosRule(long double a, long double b, long double c) {
    // Handle denom = 0
    long double res = (b * b + c * c - a * a) / (2 * b * c);
    if (fabs(res - 1) < EPS)
        res = 1;
    if (fabs(res + 1) < EPS)
        res = -1;
    return acos(res);
}

long double sinRuleAngle(long double s1, long double s2, long double a1) {
    // Handle denom = 0
    long double res = s2 * sin(a1) / s1;
    if (fabs(res - 1) < EPS)
        res = 1;
    if (fabs(res + 1) < EPS)
        res = -1;
    return asin(res);
}

long double sinRuleSide(long double s1, long double a1, long double a2) {
    // Handle denom = 0
    long double res = s1 * sin(a2) / sin(a1);
    return fabs(res);
}

int circleLineIntersection(const point &p0, const point &p1, const point &cen,
                           long double rad, point &r1, point &r2) {

    // handle degenerate case if p0 == p1
    long double a, b, c, t1, t2;
    a = dot(p1 - p0, p1 - p0);
    b = 2 * dot(p1 - p0, p0 - cen);
    c = dot(p0 - cen, p0 - cen) - rad * rad;
    double det = b * b - 4 * a * c;
    int res;
    if (fabs(det) < EPS)
        det = 0, res = 1;
    else if (det < 0)
        res = 0;
    else
        res = 2;
    det = sqrt(det);
    t1 = (-b + det) / (2 * a);
    t2 = (-b - det) / (2 * a);
    r1 = p0 + t1 * (p1 - p0);
    r2 = p0 + t2 * (p1 - p0);
    return res;
}

int circleCircleIntersection(const point &c1, const long double &r1,
                             const point &c2, const long double &r2, point &res1, point &res2) {
    if (same(c1, c2) && fabs(r1 - r2) < EPS) {
        res1 = res2 = c1;
        return fabs(r1) < EPS ? 1 : OO;
    }
    long double len = length(vec(c1, c2));
    if (fabs(len - (r1 + r2)) < EPS || fabs(fabs(r1 - r2) - len) < EPS) {
        point d, c;
        long double r;
        if (r1 > r2)
            d = vec(c1, c2), c = c1, r = r1;
        else
            d = vec(c2, c1), c = c2, r = r2;
        res1 = res2 = normalize(d) * r + c;
        return 1;
    }
    if (len > r1 + r2 || len < fabs(r1 - r2))
        return 0;
    long double a = cosRule(r2, r1, len);
    point c1c2 = normalize(vec(c1, c2)) * r1;
    res1 = rotate(c1c2, a) + c1;
    res2 = rotate(c1c2, -a) + c1;
    return 2;
}

void circle2(const point &p1, const point &p2, point &cen, long double &r) {
    cen = mid(p1, p2);
    r = length(vec(p1, p2)) / 2;
}

bool circle3(const point &p1, const point &p2, const point &p3, point &cen,
             long double &r) {
    point m1 = mid(p1, p2);
    point m2 = mid(p2, p3);
    point perp1 = perp(vec(p1, p2));
    point perp2 = perp(vec(p2, p3));
    bool res = intersect(m1, m1 + perp1, m2, m2 + perp2, cen);
    r = length(vec(cen, p1));
    return res;
}

STATE circlePoint(const point &cen, const long double &r, const point &p) {
    long double lensqr = lengthSqr(vec(cen, p));
    if (fabs(lensqr - r * r) < EPS)
        return BOUNDRY;
    if (lensqr < r * r)
        return IN;
    return OUT;
}

int tangentPoints(const point &cen, const long double &r, const point &p,
                  point &r1, point &r2) {
    STATE s = circlePoint(cen, r, p);
    if (s != OUT) {
        r1 = r2 = p;
        return s == BOUNDRY;
    }
    point cp = vec(cen, p);
    long double h = length(cp);
    long double a = acos(r / h);
    cp = normalize(cp) * r;
    r1 = rotate(cp, a) + cen;
    r2 = rotate(cp, -a) + cen;
    return 2;
}

typedef pair<point, point> segment;

void getCommonTangents(point c1, double r1, point c2, double r2, vector<segment> &res) {
    if (r1 < r2) swap(r1, r2), swap(c1, c2);
    double d = length(c1 - c2);
    double theta = acos((r1 - r2) / d);
    point v = c2 - c1;
    v = v / hypot(v.imag(), v.real());
    point v1 = v * exp(point(0, theta));
    point v2 = v * exp(point(0, -theta));
    res.clear();
    res.push_back(segment(c1 + v1 * r1, c2 + v1 * r2));
    res.push_back(segment(c1 + v2 * r1, c2 + v2 * r2));
    theta = acos((r1 + r2) / d);
    v1 = v * exp(point(0, theta));
    v2 = v * exp(point(0, -theta));
    res.push_back(segment(c1 + v1 * r1, c2 - v1 * r2));
    res.push_back(segment(c1 + v2 * r1, c2 - v2 * r2));
}

// minimum enclosing circle
//init p array with the points and ps with the number of points
//cen and rad are result circle
//you must call random_shuffle(p,p+ps); before you call mec
#define MAXPOINTS 100000
point p[MAXPOINTS], r[3], cen;
int ps, rs;
long double rad;

void mec() {
    if (rs == 3) {
        circle3(r[0], r[1], r[2], cen, rad);
        return;
    }
    if (rs == 2 && ps == 0) {
        circle2(r[0], r[1], cen, rad);
        return;
    }
    if (!ps) {
        cen = r[0];
        rad = 0;
        return;
    }
    ps--;
    mec();
    if (circlePoint(cen, rad, p[ps]) == OUT) {
        r[rs++] = p[ps];
        mec();
        rs--;
    }
    ps++;

}

//to check if the points are sorted anti-clockwise or clockwise
//remove the fabs at the end and it will return -ve value if clockwise
long double polygonArea(const vector<point> &p) {
    long double res = 0;
    for (int i = 0; i < sz(p); i++) {
        int j = (i + 1) % sz(p);
        res += cross(p[i], p[j]);
    }
    return fabs(res) / 2;
}

// return the centroid point of the polygon
// The centroid is also known as the "centre of gravity" or the "center of mass". The position of the centroid
// assuming the polygon to be made of a material of uniform density.
point polyginCentroid(vector<point> &polygon) {
    long double a = 0;
    long double x = 0.0, y = 0.0;
    for (int i = 0; i < (int) polygon.size(); i++) {
        int j = (i + 1) % polygon.size();

        x += (polygon[i].X + polygon[j].X) * (polygon[i].X * polygon[j].Y
                                              - polygon[j].X * polygon[i].Y);

        y += (polygon[i].Y + polygon[j].Y) * (polygon[i].X * polygon[j].Y
                                              - polygon[j].X * polygon[i].Y);

        a += polygon[i].X * polygon[j].Y - polygon[i].Y * polygon[j].X;
    }

    a *= 0.5;
    x /= 6 * a;
    y /= 6 * a;

    return point(x, y);
}

int picksTheorm(vector<point> &p) {
    long double area = 0;
    int bound = 0;
    for (int i = 0; i < sz(p); i++) {
        int j = (i + 1) % sz(p);
        area += cross(p[i], p[j]);
        point v = vec(p[i], p[j]);
        bound += abs(__gcd((int) v.X, (int) v.Y));
    }
    area /= 2;
    area = fabs(area);
    return round(area - bound / 2 + 1);
}

void polygonCut(const vector<point> &p, const point &a, const point &b, vector<
        point> &res) {
    res.clear();
    for (int i = 0; i < sz(p); i++) {
        int j = (i + 1) % sz(p);
        bool in1 = cross(vec(a, b), vec(a, p[i])) > EPS;
        bool in2 = cross(vec(a, b), vec(a, p[j])) > EPS;
        if (in1)
            res.push_back(p[i]);
        if (in1 ^ in2) {
            point r;
            intersect(a, b, p[i], p[j], r);
            res.push_back(r);
        }
    }
}

//assume that both are anti-clockwise
void convexPolygonIntersect(const vector<point> &p, const vector<point> &q,
                            vector<point> &res) {
    res = q;
    for (int i = 0; i < sz(p); i++) {
        int j = (i + 1) % sz(p);
        vector<point> temp;
        polygonCut(res, p[i], p[j], temp);
        res = temp;
        if (res.empty())
            return;
    }
}

void voronoi(const vector<point> &pnts, const vector<point> &rect, vector<
        vector<point> > &res) {
    res.clear();
    for (int i = 0; i < sz(pnts); i++) {
        res.push_back(rect);
        for (int j = 0; j < sz(pnts); j++) {
            if (j == i)
                continue;
            point p = perp(vec(pnts[i], pnts[j]));
            point m = mid(pnts[i], pnts[j]);
            vector<point> temp;
            polygonCut(res.back(), m, m + p, temp);
            res.back() = temp;
        }
    }
}

STATE pointInPolygon(const vector<point> &p, const point &pnt) {
    point p2 = pnt + point(1, 0);
    int cnt = 0;
    for (int i = 0; i < sz(p); i++) {
        int j = (i + 1) % sz(p);
        if (pointOnSegment(p[i], p[j], pnt))
            return BOUNDRY;
        point r;
        if (!intersect(pnt, p2, p[i], p[j], r))
            continue;
        if (!pointOnRay(pnt, p2, r))
            continue;
        if (same(r, p[i]) || same(r, p[j]))
            if (fabs(r.Y - min(p[i].Y, p[j].Y)) < EPS)
                continue;
        if (!pointOnSegment(p[i], p[j], r))
            continue;
        cnt++;
    }
    return cnt & 1 ? IN : OUT;
}

struct cmp {
    point about;
    cmp(point c) {
        about = c;
    }
    bool operator()(const point &p, const point &q) const {
        double cr = cross(vec(about, p), vec(about, q));
        if (fabs(cr) < EPS)
            return make_pair(p.Y, p.X) < make_pair(q.Y, q.X);
        return cr > 0;
    }
};

void sortAntiClockWise(vector<point> &pnts) {
    point mn(1 / 0.0, 1 / 0.0);
    for (int i = 0; i < sz(pnts); i++)
        if (make_pair(pnts[i].Y, pnts[i].X) < make_pair(mn.Y, mn.X))
            mn = pnts[i];

    sort(all(pnts), cmp(mn));
}

void convexHull(vector<point> pnts, vector<point> &convex) {
    sortAntiClockWise(pnts);
    convex.clear();
    convex.push_back(pnts[0]);
    if (sz(pnts) == 1)
        return;
    convex.push_back(pnts[1]);
    if (sz(pnts) == 2) {
        if (same(pnts[0], pnts[1]))
            convex.pop_back();
        return;
    }
    for (int i = 2; i <= sz(pnts); i++) {
        point c = pnts[i % sz(pnts)];
        while (sz(convex) > 1) {
            point b = convex.back();
            point a = convex[sz(convex) - 2];
            if (cross(vec(b, a), vec(b, c)) < -EPS)
                break;
            convex.pop_back();
        }
        if (i < sz(pnts))
            convex.push_back(pnts[i]);
    }
}


bool pointInTriangle(point a, point b, point c, point pt) {
    ll s1 = abs(cross(b - a, c - a));
    a -= pt, b -= pt, c -= pt;
    ll s2 = abs(cross(a, b)) + abs(cross(b, c)) + abs(cross(c, a));
    return s1 == s2;
}

//assume p is ordered anticlockwise and p[0] has minimal {y, x}
bool pointInConvexPolygon(const vector<point> &p, point pnt) {
    int n = p.size();
    pnt = pnt - p[0];
    point fst = p[1] - p[0];
    point lst = p[n - 1] - p[0];

    if (cross(fst, pnt) != 0 &&
        sgn(cross(fst, pnt)) != sgn(cross(fst, lst)))
        return false;
    if (cross(lst, pnt) != 0 &&
        sgn(cross(lst, pnt)) != sgn(cross(lst, fst)))
        return false;

    if (cross(fst, pnt) == 0)
        return lengthSqr(fst) >= lengthSqr(pnt);

    int l = 1, r = n - 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        int pos = mid;
        if (cross(p[pos] - p[0], pnt) >= 0)
            l = mid;
        else
            r = mid;
    }
    int pos = l;
    return pointInTriangle(p[pos], p[pos + 1], p[0], pnt + p[0]);
}

double adaptiveSimpsonsAux(function<double(const double &)> f, double a, double b, double eps,
                           double whole, double fa, double fb, double fm, int rec) {
    double m = (a + b) / 2, h = (b - a) / 2;
    double lm = (a + m) / 2, rm = (m + b) / 2;
    // serious numerical trouble: it won't converge
    if ((eps / 2 == eps) || (a == lm)) {
        errno = EDOM;
        return whole;
    }
    double flm = f(lm), frm = f(rm);
    double left = (h / 6) * (fa + 4 * flm + fm);
    double right = (h / 6) * (fm + 4 * frm + fb);
    double delta = left + right - whole;

    if (rec <= 0 && errno != EDOM) errno = ERANGE;  // depth limit too shallow
    // Lyness 1969 + Richardson extrapolation; see article
    if (rec <= 0 || fabs(delta) <= 15 * eps)
        return left + right + (delta) / 15;
    return adaptiveSimpsonsAux(f, a, m, eps / 2, left, fa, fm, flm, rec - 1) +
           adaptiveSimpsonsAux(f, m, b, eps / 2, right, fm, fb, frm, rec - 1);
}

/** Adaptive Simpson's Rule Wrapper
 *  (fills in cached function evaluations) */
double adaptiveSimpsons(function<double(const double &)> f,     // function ptr to integrate
                        double a, double b,      // interval [a,b]
                        double epsilon,         // error tolerance
                        int maxRecDepth) {     // recursion cap
    errno = 0;
    double h = b - a;
    if (h == 0) return 0;
    double fa = f(a), fb = f(b), fm = f((a + b) / 2);
    double S = (h / 6) * (fa + 4 * fm + fb);
    return adaptiveSimpsonsAux(f, a, b, epsilon, S, fa, fb, fm, maxRecDepth);
}
