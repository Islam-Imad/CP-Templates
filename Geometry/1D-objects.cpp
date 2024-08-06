#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

const double EPS = 1e-9;
const double PI = acos(-1.0);
int dcmp(double x, double y) { return fabs(x - y) <= EPS ? 0 : (x < y ? -1 : 1); }

double deg_to_rad(double deg) { return deg * PI / 180.0; }
double rad_to_deg(double rad) { return rad * 180.0 / PI; }

struct point
{
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
    bool operator==(point other) const
    {
        return (dcmp(x, other.x) == 0 && dcmp(y, other.y) == 0);
    }
    bool operator<(point other) const
    {
        return (dcmp(x, other.x) == 0 ? y < other.y : x < other.x);
    }
    point rotate(double angle)
    {
        double rad = deg_to_rad(angle);
        return point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));
    }
    double dist(point p)
    {
        return hypot(x - p.x, y - p.y);
    }
};

struct line
{
    double a, b, c;

    line(point p1, point p2)
    {
        if (dcmp(p1.x, p2.x) == 0)
        {
            a = 1.0, b = 0.0, c = -p1.x;
        }
        else
        {
            a = -(p1.y - p2.y) / (p1.x - p2.x);
            b = 1.0;
            c = -(a * p1.x) - p1.y;
        }
    }

    bool parallel(line l)
    {
        return (dcmp(a, l.a) == 0 && dcmp(b, l.b) == 0);
    }

    bool same(line l)
    {
        return (parallel(l) && dcmp(c, l.c) == 0);
    }

    point intersection(line l)
    {
        if (parallel(l))
            return point(1e18, 1e18);
        double x = (b * l.c - c * l.b) / (a * l.b - b * l.a);
        double y = -(a * x + c) / b;
        return point(x, y);
    }
};

void solve()
{
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin>>tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}