#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#define ld long double
const ld EPS = 1e-9;
const ld PI = acos(-1);

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

struct pt
{
    ld x, y;
    pt() : x(0), y(0) {}
    pt(ld x, ld y) : x(x), y(y) {}
    pt operator+(const pt &p) const { return pt(x + p.x, y + p.y); }
    pt operator-(const pt &p) const { return pt(x - p.x, y - p.y); }
    pt operator*(ld k) const { return pt(x * k, y * k); }
    pt operator/(ld k) const { return pt(x / k, y / k); }

    bool operator==(const pt &a) const { return dcmp(x, a.x) == 0 && dcmp(y, a.y) == 0; }
    bool operator!=(const pt &a) const { return dcmp(x, a.x) != 0 || dcmp(y, a.y) != 0; }

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

pt unit(const pt &p)
{
    return p / abs(p);
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

/// @brief Computes the angle between two vectors
/// @param a The first vector
/// @param b The second vector
/// @return The angle between the two vectors in radians   0 <= angle <= PI
ld angle(const pt &a, const pt &b)
{
    ld val = dot(a, b) / (abs(a) * abs(b));
    // Clamp value between -1 and 1
    if (val > 1.0)
        val = 1.0;
    if (val < -1.0)
        val = -1.0;
    ld res = acos(val);
    if (res < 0)
        res = 0;
    if (res > PI)
        res = PI;
    return res;
}

ld angle(const pt &a)
{
    return atan2l(a.y, a.x);
}

struct line
{
    pt v;
    ld c;
    line(const pt &v, ld c) : v(v), c(c) {}
    line(ld a, ld b, ld c) : v({b, -a}), c(c) {}
    line(const pt &p, const pt &q) : v(q - p), c(cross(v, p)) {}

    ld side(const pt &p) const
    {
        return cross(v, p) - c;
    }

    ld dist(const pt &p) const
    {
        return abs(side(p)) / abs(v);
    }

    ld sq_dist(const pt &p) const
    {
        return side(p) * side(p) / (ld)sq(v);
    }

    line perp_through(const pt &p) const
    {
        return {p, p + perp(v)};
    }

    pt proj(const pt &p) const
    {
        return p - perp(v) * side(p) / sq(v);
    }
};

bool inter(const line &l1, const line &l2, pt &out)
{
    ld d = cross(l1.v, l2.v);
    if (dcmp(d, 0) == 0)
        return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

line bisector(const line &l1, const line &l2, bool interior)
{
    assert(cross(l1.v, l2.v) != 0);
    ld sign = interior ? 1 : -1;
    return {unit(l1.v) + unit(l2.v) * sign, l1.c / abs(l1.v) + l2.c / abs(l2.v) * sign};
}

istream &operator>>(istream &is, pt &p)
{
    return is >> p.x >> p.y;
}

istream &operator>>(istream &is, line &l)
{
    return is >> l.v >> l.c;
}

ostream &operator<<(ostream &os, const pt &p)
{
    return os << p.x << " " << p.y;
}

ostream &operator<<(ostream &os, const line &l)
{
    return os << -l.v.y << " " << l.v.x << " " << -l.c;
}

ld cosine_rule(ld a, ld b, ld c)
{
    return (a * a + b * b - c * c) / (2.0 * a * b);
}

ld sine_rule(ld a, ld b, ld c)
{
    // The sine rule: a/sin(A) = b/sin(B) = c/sin(C) = 2R
    // where R is the circumradius
    ld a_angle = acosl(cosine_rule(b, c, a));
    return a / (sinl(a_angle)); // Returns circumradius R
}

ld get_angle(ld a, ld b, ld c)
{
    ld cos_val = cosine_rule(a, b, c);
    // Clamp value between -1 and 1
    // if (cos_val > 1.0)
    //     cos_val = 1.0;
    // if (cos_val < -1.0)
    //     cos_val = -1.0;
    return acos(cos_val);
}

struct circle
{
    pt o;
    ld r;
    circle(pt o, ld r) : o(o), r(r) {}
    circle() : o(pt()), r(0) {}

    bool operator==(const circle &c) const
    {
        return o == c.o && dcmp(r, c.r) == 0;
    }

    bool operator!=(const circle &c) const
    {
        return !(*this == c);
    }
};

istream &operator>>(istream &is, circle &c)
{
    return is >> c.o >> c.r;
}

ostream &operator<<(ostream &os, const circle &c)
{
    return os << c.o << " " << c.r;
}

bool is_circle_inside(const circle &c1, const circle &c2)
{
    // Check if c1 is inside c2
    return dcmp(abs(c1.o - c2.o), c2.r - c1.r) <= 0;
}

ld circle_circumference(const circle &c)
{
    return 2.0 * PI * c.r;
}

ld circle_area(const circle &c)
{
    return PI * c.r * c.r;
}

ld circle_sector(const circle &c, ld angle)
{
    return c.r * c.r * angle * 0.5;
}

ld circle_segment(ld angle, const circle &c)
{
    return 0.5 * c.r * c.r * (angle - sinl(angle));
}

ld circle_triangle_area(const circle &c, ld angle)
{
    return circle_sector(c, angle) - circle_segment(angle, c);
}

int tangents(const circle &c1, const circle &c2, bool inner, vector<pair<pt, pt>> &out)
{
    ld r1 = c1.r, r2 = c2.r;
    pt o1 = c1.o, o2 = c2.o;
    if (inner)
        r2 = -r2;
    pt d = o2 - o1;
    ld dr = r1 - r2, d2 = sq(d), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0)
    {
        assert(h2 != 0);
        return 0;
    }
    for (ld sign : {-1, 1})
    {
        pt v = (d * dr + perp(d) * sqrt(h2) * sign) / d2;
        out.push_back({o1 + v * r1, o2 + v * r2});
    }
    return 1 + (h2 > 0);
}

bool circle_circle_intersection(const circle &c1, const circle &c2, pair<pt, pt> &out)
{
    ld d = abs(c2.o - c1.o);
    if (d < abs(c2.r - c1.r) || d > c1.r + c2.r)
        return false;
    ld co = (c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d);
    if (co < -1 || co > 1)
        return false;
    ld alpha = acos((d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d * c1.r));
    pt rad = (c2.o - c1.o) / d * c1.r;
    out = {c1.o + rotate(rad, -alpha), c1.o + rotate(rad, alpha)};
    return true;
}

int circle_line_intersection(const circle &cir, line l, pair<pt, pt> &out)
{
    ld h2 = cir.r * cir.r - l.sq_dist(cir.o);
    if (h2 >= 0)
    {                                     // the line touches the circle
        pt p = l.proj(cir.o);             // point P
        pt h = l.v * sqrt(h2) / abs(l.v); // vector parallel to l, of length h
        out = {p - h, p + h};
    }
    return 1 + sign(h2);
}

ld cir_area_cut(ld a, ld r)
{
    ld s1 = a * r * r / 2;
    ld s2 = sinl(a) * r * r / 2;
    return s1 - s2;
}

ld common_circle_area(circle c1, circle c2)
{ // return the common area of two circle
    if (c1.r < c2.r)
        swap(c1, c2);
    ld d = abs(c1.o - c2.o);
    if (d + c2.r <= c1.r + EPS)
        return c2.r * c2.r * PI;
    if (d >= c1.r + c2.r - EPS)
        return 0.0;
    ld a1 = acosl(cosine_rule(d, c1.r, c2.r));
    ld a2 = acosl(cosine_rule(d, c2.r, c1.r));
    return circle_segment(a1 * 2.0, c1) + circle_segment(a2 * 2.0, c2);
}

ld triangle_area(ld a, ld b, ld c)
{
    // Heron's formula
    ld s = (a + b + c) / 2.0;
    return sqrtl(s * (s - a) * (s - b) * (s - c));
}

circle outside_circle(pt a, pt b, pt c)
{
    pt ab = b - a;
    pt ac = c - a;
    assert(cross(ab, ac) != 0); // no circumcircle if A,B,C aligned
    pt center = a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2;
    ld radius = abs(center - a);
    return circle(center, radius);
}

circle inside_circle(pt a, pt b, pt c)
{
    ld sa = abs(b - c);
    ld sb = abs(c - a);
    ld sc = abs(a - b);
    ld area = triangle_area(sa, sb, sc);
    ld r = (2 * area) / (sa + sb + sc);
    ld x = (a.x * sa + b.x * sb + c.x * sc) / (sa + sb + sc);
    ld y = (a.y * sa + b.y * sb + c.y * sc) / (sa + sb + sc);
    pt center = {x, y};
    return circle(center, r);
}

ld triangle_area(pt a, pt b, pt c)
{
    return abs(cross(b - a, c - a)) / 2.0;
}

vector<ld> bary(pt a, pt b, pt c, pt p)
{
    vector<ld> res(3);
    ld ta = triangle_area(a, b, c);
    res[0] = triangle_area(p,b,c) / ta;
    res[1] = triangle_area(a,p,c) / ta;
    res[2] = triangle_area(a,b,p) / ta;
    return res;
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

// pt points_to_center2(pt a, pt b, pt c)
// {
//     line ab(a, b);
//     line ac(a, c);
//     pt mid_ab = (a + b) / 2;
//     pt mid_ac = (a + c) / 2;
//     line perp_ab = ab.perp_through(mid_ab);
//     line perp_ac = ac.perp_through(mid_ac);
//     pt inter_pt;
//     assert(inter(perp_ab, perp_ac, inter_pt));
//     return inter_pt;
// }

// circle points_to_circle2(pt a, pt b, pt c)
// {
//     pt center = points_to_center2(a, b, c);
//     ld radius = abs(center - a);
//     return circle(center, radius);
// }

// int circle_circle_intersection2(const circle &c1, const circle &c2, pair<pt, pt> &out)
// {
//     pt d = c2.o - c1.o;
//     ld d2 = sq(d);
//     if (d2 == 0)
//     {
//         assert(c1.r != c2.r);
//         return 0;
//     } // concentric circles
//     ld pd = (d2 + c1.r * c1.r - c2.r * c2.r) / 2; // = |O_1P| * d
//     ld h2 = c1.r * c1.r - pd * pd / d2;           // = hˆ2
//     if (h2 >= 0)
//     {
//         pt p = c1.o + d * pd / d2, h = perp(d) * sqrt(h2 / d2);
//         out = {p - h, p + h};
//     }
//     return 1 + sign(h2);
// }