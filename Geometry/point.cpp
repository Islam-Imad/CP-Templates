#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#define ld double
const ld EPS = 1e-9;

int dcmp(ld a, ld b)
{
    if (fabs(a - b) < EPS)
        return 0;
    return (a < b) ? -1 : 1;
}

int sign(ld a)
{
    return dcmp(a, 0.0);
}

int quadRoots(ld a, ld b, ld c, pair<ld, ld> &out)
{
    assert(a != 0);
    ld disc = b * b - 4 * a * c;
    if (disc < 0)
        return 0;
    ld sum = (b >= 0) ? -b - sqrt(disc) : -b + sqrt(disc);
    out = {sum / (2 * a), sum == 0 ? 0 : (2 * c) / sum};
    return 1 + (disc > 0);
}

struct pt
{
    ld x, y;
    pt() : x(0), y(0) {}
    pt(ld x, ld y) : x(x), y(y) {}
    pt operator+(const pt &p) const { return pt(x + p.x, y + p.y); }
    pt operator-(const pt &p) const { return pt(x - p.x, y - p.y); }
    pt operator*(ld k) const { return pt(x * k, y * k); }
    pt operator/(ld k) const { return pt(x / k, y / k); }

    bool operator==(pt a) { return dcmp(x, a.x) == 0 and dcmp(y, a.y) == 0; }
    bool operator!=(pt a) { return dcmp(x, a.x) != 0 or dcmp(y, a.y) != 0; }

    bool operator<(pt p) const
    {
        return dcmp(x, p.x) < 0 || (dcmp(x, p.x) == 0 && dcmp(y, p.y) < 0);
    }

    bool operator>(pt p) const
    {
        return dcmp(x, p.x) > 0 || (dcmp(x, p.x) == 0 && dcmp(y, p.y) > 0);
    }

    bool operator<=(pt p) const
    {
        return dcmp(x, p.x) < 0 || (dcmp(x, p.x) == 0 && dcmp(y, p.y) <= 0);
    }

    bool operator>=(pt p) const
    {
        return dcmp(x, p.x) > 0 || (dcmp(x, p.x) == 0 && dcmp(y, p.y) >= 0);
    }
};

ld sq(const pt &a)
{
    return a.x * a.x + a.y * a.y;
}

ld abs(const pt &a)
{
    return sqrtl(sq(a));
}

pt scale(const pt &a, const pt &c, ld factor)
{
    return c + (a - c) * factor;
}

pt translate(const pt &a, const pt &t)
{
    return (a) + t;
}

pt rotate(const pt &a, ld angle)
{
    return {a.x * cos(angle) - a.y * sin(angle), a.x * sin(angle) + a.y * cos(angle)};
}

pt rotate(const pt &a, const pt &p, ld angle)
{
    return p + rotate(a - p, angle);
}

pt perp(const pt &a)
{
    return {-a.y, a.x};
}

ld dot(const pt &a, const pt &v)
{
    return a.x * v.x + a.y * v.y;
}

ld cross(const pt &a, const pt &v)
{
    return a.x * v.y - a.y * v.x;
}

ld angle(const pt &a, const pt &b)
{
    return acos(clamp(dot(a, b) / (abs(a) * abs(b)), ld(-1.0), ld(1.0)));
}

ld angle(const pt &a)
{
    return atan2l(a.y, a.x);
}

bool is_perp(const pt &a, const pt &b)
{
    return dot(a, b) == 0;
}

pt linear_transformation(pt p, pt q, pt r, pt fp, pt fq)
{
    pt pq = q - p;
    pt num = pt(cross(pq, fq - fp), dot(pq, fq - fp));
    return fp + pt(-1 * cross(num, r - p), dot(num, r - p)) / sq(pq);
}

bool circleCircle(pt c1, ld r1, pt c2, ld r2, pair<pt, pt> &out)
{
    ld d = abs(c2 - c1);
    if (d < abs(r2 - r1) || d > r1 + r2) // triangle inequalities
        return false;
    ld co = (r1 * r1 + d * d - r2 * r2) / (2 * r1 * d);
    if (co < -1 || co > 1) // r1 and r2 are too far apart
        return false;
    ld alpha = acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
    pt rad = (c2 - c1) / d * r1; // vector C1C2 resized to have length r1
    out = {c1 + rotate(rad, -alpha), c1 + rotate(rad, alpha)};
    return true;
}

void solve()
{
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef LOCAL_IO
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin>>tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}