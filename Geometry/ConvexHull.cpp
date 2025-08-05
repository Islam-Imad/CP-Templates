#include <bits/stdc++.h>
using namespace std;

#define sz(v) ((int)((v).size()))
#define ll long long int
const int OO = (int)1e8; // Note: Small->WRONG, Large->OVERFLOW

const double PI = acos(-1.0);

const double EPS = (1e-8); // use lower carefully, e.g. for binary search

int dcmp(double a, double b) { return fabs(a - b) <= EPS ? 0 : a < b ? -1
                                                                     : 1; }

typedef complex<ll> point;
#define X real()
#define Y imag()
#define angle(a) (atan2((a).imag(), (a).real()))
#define vec(a, b) ((b) - (a))
#define same(p1, p2) (dp(vec(p1, p2), vec(p1, p2)) < EPS)
#define dp(a, b) ((conj(a) * (b)).real()) // a*b cos(T), if zero -> prep
#define cp(a, b) ((conj(a) * (b)).imag()) // a*b sin(T), if zero -> parallel
#define length(a) (hypot((a).imag(), (a).real()))
#define normalize(a) (a) / length(a)
#define polar(r, ang) ((r) * exp(point(0, ang)))
#define rotateO(p, ang) ((p) * exp(point(0, ang)))
#define rotateA(p, ang, about) (rotateO(vec(about, p), ang) + about)

point reflect(point p, point p0, point p1)
{
    point z = p - p0, w = p1 - p0;
    return conj(z / w) * w + p0; // Reflect point p1 around p0p1
}

struct angleCMP
{
    point center;
    angleCMP(point c) : center(c) {}
    bool operator()(const point &p0, const point &p1)
    {
        if (dcmp(cp(p0 - center, p1 - center), 0) == 0)
            if (dcmp(p0.Y, p1.Y) == 0)
                return dcmp(p0.X, p1.X) < 0;
            else
                return dcmp(p0.Y, p1.Y) < 0;
        return cp(p0 - center, p1 - center) > 0;
    }
};

vector<point> ConvexHull(vector<point> points)
{
    if (sz(points) <= 1)
        return points;

    for (int i = 0; i < sz(points); ++i)
        if (make_pair(points[i].Y, points[i].X) < make_pair(points[0].Y, points[0].X))
            swap(points[0], points[i]);
    sort(points.begin() + 1, points.end(), angleCMP(points[0]));
    vector<point> p, ch;

    /*
    //To remove co-linear points, un-comment this part
    */
    // for (int i = 0; i < sz(points); ++i)
    // {
    //     if (sz(p) > 1 && !cp(p.back() - p[0], points[i] - p[0]))
    //     {
    //         if (length(points[0] - p.back()) < length(points[0] - points[i]))
    //             p.back() = points[i];
    //     }
    //     else
    //         p.push_back(points[i]);
    // }
    // points = p;
    int s = 0;
    for (int t = 0; t < 2; ++t)
    {
        for (int i = 0; i < sz(points); ++i)
        {
            while ((sz(ch) - s >= 2) && cp(points[i] - ch[sz(ch) - 1], ch[sz(ch) - 2] - ch[sz(ch) - 1]) < 0)
            {
                ch.pop_back(); // ALSO Make it <= to remove co-linear points
            }
            ch.push_back(points[i]);
        }
        reverse(points.begin(), points.end());
        ch.pop_back();
        s = sz(ch);
    }
    return ch;
}

bool isConvex(const vector<point> &c)
{
    int n = sz(c);
    if (n < 3)
        return false;
    bool pos = false, neg = false;
    for (int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n, k = (i + 2) % n;
        ll cross = cp(vec(c[j], c[i]), vec(c[k], c[i]));
        if (cross > 0)
            pos = true;
        else if (cross < 0)
            neg = true;
    }
    return !(pos && neg);
}

ll getConvexArea(const vector<point> &c)
{
    ll area = 0;
    for (int i = 0; i < sz(c) - 1; ++i)
    {
        int j = i + 1;
        area += ((ll)c[i].X * (ll)c[j].Y - (ll)c[j].X * (ll)c[i].Y);
    }
    return abs(area);
}