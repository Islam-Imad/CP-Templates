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

pt unit(const pt &p)
{
    return p / abs(p);
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

/// @brief Computes the angle between two vectors
/// @param a The first vector
/// @param b The second vector
/// @return The angle between the two vectors in radians   0 <= angle <= PI
ld angle(const pt &a, const pt &b)
{
    ld val = dot(a, b) / (abs(a) * abs(b));
    // Clamp value between -1 and 1
    if (val > 1.0) val = 1.0;
    if (val < -1.0) val = -1.0;
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

ld orient(const pt &a, const pt &b, const pt &c)
{
    return cross(b - a, c - a);
}

ld orient_angle(pt a, pt b, pt c)
{
    if (orient(a, b, c) >= 0)
        return angle(b - a, c - a);
    return 2 * PI - angle(b - a, c - a);
}

bool in_angle(pt a, pt b, pt c, pt x)
{
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0)
        swap(b, c);
    return orient(a, b, x) >= 0 && orient(a, c, x) <= 0;
}

bool is_convex(const vector<pt> &p)
{
    bool has_pos = false, has_neg = false;
    for (int i = 0, n = p.size(); i < n; i++)
    {
        ld o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0)
            has_pos = true;
        if (o < 0)
            has_neg = true;
    }
    return !(has_pos && has_neg);
}

bool half(const pt &p)
{
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

bool half(const pt &p, const pt &v)
{
    return cross(p, v) < 0 || (cross(p, v) == 0 && dot(p, v) < 0);
}

void polar_sort(vector<pt> &v)
{
    sort(v.begin(), v.end(), [](pt a, pt b)
         { return make_tuple(half(a), 0, sq(a)) < make_tuple(half(b), cross(a, b), sq(b)); });
}

void polar_sort(pt &o, vector<pt> &v)
{
    sort(v.begin(), v.end(), [&](pt a, pt b)
         { return make_tuple(half(a - o), 0, sq(a - o)) < make_tuple(half(b - o), cross(a - o, b - o), sq(b - o)); });
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

    bool cmp_proj(const pt &p, const pt &q) const
    {
        return dot(v, p) < dot(v, q);
    }

    line translate(const pt &t) const
    {
        return {v, c + cross(v, t)};
    }

    line shift_left(ld dist) const
    {
        return {v, c + dist * abs(v)};
    }

    pt proj(const pt &p) const
    {
        return p - perp(v) * side(p) / sq(v);
    }

    pt refl(const pt &p) const
    {
        return p - perp(v) * 2 * side(p) / sq(v);
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

bool in_disk(const pt &a, const pt &b, const pt &p)
{
    return dcmp(dot(a - p, b - p), 0) <= 0;
}

bool on_segment(const pt &a, const pt &b, const pt &p)
{
    return dcmp(orient(a, b, p), 0) == 0 && in_disk(a, b, p);
}

ld seg_point(pt a, pt b, pt p)
{
    if (a != b)
    {
        line l(a, b);
        if (l.cmp_proj(a, p) && l.cmp_proj(p, b))
            return l.dist(p);
    }
    return min(abs(p - a), abs(p - b));
}

bool proper_inter(pt a, pt b, pt c, pt d, pt &out)
{
    ld oa = orient(c, d, a);
    ld ob = orient(c, d, b);
    ld oc = orient(a, b, c);
    ld od = orient(a, b, d);
    if (oa * ob < 0 && oc * od < 0)
    {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

/// @brief Computes the area of a triangle
/// @param a The first vertex of the triangle
/// @param b The second vertex of the triangle
/// @param c The third vertex of the triangle
/// @return The area of the triangle
ld areaTriangle(pt a, pt b, pt c)
{
    return abs(cross(b - a, c - a)) * 0.5;
}

/// @brief Computes the area of a polygon
/// @param p The vertices of the polygon in counter-clockwise order
/// @return The area of the polygon
ld areaPolygon(vector<pt> p)
{
    ld area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++)
    {
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n
    }
    return abs(area) * 0.5;
}

/// @brief Checks if point p is above line defined by point a
/// @param a The point defining the line
/// @param p The point to check
/// @return True if p is above the line, false otherwise
bool above(pt a, pt p)
{
    return p.y >= a.y;
}

/// @brief Checks if line segment [PQ] crosses ray from A
/// @param a The point defining the ray
/// @param p The first endpoint of the segment
/// @param q The second endpoint of the segment
/// @return True if the segment crosses the ray, false otherwise
bool crossesRay(pt a, pt p, pt q)
{
    return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
}

bool inPolygon(vector<pt> p, pt a, bool strict = true)
{
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++)
    {
        if (on_segment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}

pt circumCenter(pt a, pt b, pt c)
{
    b = b - a, c = c - a;     // consider coordinates relative to A
    assert(cross(b, c) != 0); // no circumcircle if A,B,C aligned
    return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2;
}

pt circumCenter2(pt a, pt b, pt c)
{
    line ab(a, b);
    line ac(a, c);
    pt mid_ab = (a + b) / 2;
    pt mid_ac = (a + c) / 2;
    line perp_ab = ab.perp_through(mid_ab);
    line perp_ac = ac.perp_through(mid_ac);
    pt inter_pt;
    assert(inter(perp_ab, perp_ac, inter_pt));
    return inter_pt;
}

int circleLine(pt o, ld r, line l, pair<pt, pt> &out)
{
    ld h2 = r * r - l.sq_dist(o);
    if (h2 >= 0)
    {                                     // the line touches the circle
        pt p = l.proj(o);                 // point P
        pt h = l.v * sqrt(h2) / abs(l.v); // vector parallel to l, of length h
        out = {p - h, p + h};
    }
    return 1 + sign(h2);
}

int circleCircle2(pt o1, ld r1, pt o2, ld r2, pair<pt, pt> &out)
{
    pt d = o2 - o1;
    ld d2 = sq(d);
    if (d2 == 0)
    {
        assert(r1 != r2);
        return 0;
    } // concentric circles
    ld pd = (d2 + r1 * r1 - r2 * r2) / 2; // = |O_1P| * d
    ld h2 = r1 * r1 - pd * pd / d2;       // = hˆ2
    if (h2 >= 0)
    {
        pt p = o1 + d * pd / d2, h = perp(d) * sqrt(h2 / d2);
        out = {p - h, p + h};
    }
    return 1 + sign(h2);
}

int tangents(pt o1, ld r1, pt o2, ld r2, bool inner, vector<pair<pt, pt>> &out)
{
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

void solve()
{
    pt c1, c2;
    ld r1, r2;
    cin >> c1 >> r1 >> c2 >> r2;
    vector<pair<pt, pt>> inter1;
    vector<pair<pt, pt>> inter2;
    cout << tangents(c1, r1, c2, r2, false, inter1) + tangents(c1, r1, c2, r2, true, inter2) << '\n';
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