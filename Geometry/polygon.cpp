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

template <typename T>
T c_lamp(T x, T a, T b)
{
    if (x < a)
        return a;
    if (x > b)
        return b;
    return x;
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

ld angle(const pt &a, const pt &b)
{
    assert(abs(a) > 0 && abs(b) > 0);
    ld temp = c_lamp<ld>(dot(a, b) / (abs(a) * abs(b)), (ld)(-1.0), (ld)(1.0));
    return acosl(temp);
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

bool half(const pt &p)
{
    // assert(p.x != 0 || p.y != 0);
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

set<pt> inters(pt a, pt b, pt c, pt d)
{
    pt out;
    if (proper_inter(a, b, c, d, out))
        return {out};
    set<pt> s;
    if (on_segment(c, d, a))
        s.insert(a);
    if (on_segment(c, d, b))
        s.insert(b);
    if (on_segment(a, b, c))
        s.insert(c);
    if (on_segment(a, b, d))
        s.insert(d);
    return s;
}

ld seg_seg(pt a, pt b, pt c, pt d)
{
    pt dummy;
    if (proper_inter(a, b, c, d, dummy))
        return 0;
    return min({seg_point(a, b, c), seg_point(a, b, d),
                seg_point(c, d, a), seg_point(c, d, b)});
}

vector<pt> convex_hull(const vector<pt> &points, bool remove_redundant = true)
{
    vector<pt> pts = points;
    pt leftmost = pts[0];
    for (const auto &p : pts)
    {
        if (dcmp(p.y, leftmost.y) < 0 || (dcmp(p.y, leftmost.y) == 0 && dcmp(p.x, leftmost.x) < 0))
        {
            leftmost = p;
        }
    }
    polar_sort(leftmost, pts);
    // sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<pt> up;
    vector<pt> down;
    // cout << "why " << sz(pts) << '\n';
    for (int i = 0; i < sz(pts); ++i)
    {
        if (remove_redundant)
        {
            while (sz(up) >= 2 && orient(up[sz(up) - 2], up[sz(up) - 1], pts[i]) >= 0)
            {
                up.pop_back();
            }
            while (sz(down) >= 2 && orient(down[sz(down) - 2], down[sz(down) - 1], pts[i]) <= 0)
            {
                down.pop_back();
            }
        }
        else
        {
            while (sz(up) >= 2 && orient(up[sz(up) - 2], up[sz(up) - 1], pts[i]) > 0)
            {
                up.pop_back();
            }
            while (sz(down) >= 2 && orient(down[sz(down) - 2], down[sz(down) - 1], pts[i]) < 0)
            {
                down.pop_back();
            }
        }
        up.push_back(pts[i]);
        down.push_back(pts[i]);
    }
    pts = down;
    for (int i = sz(up) - 2; i >= 1; --i)
    {
        pts.push_back(up[i]);
    }

    if (remove_redundant)
    {
        if (sz(pts) <= 2)
        {
            return pts;
        }
        down.clear();
        down.push_back(pts[0]);
        down.push_back(pts[1]);
        for (int i = 2; i < sz(pts); ++i)
        {
            if (on_segment(down[sz(down) - 2], pts[i], down.back()))
            {
                down.pop_back();
            }
            down.push_back(pts[i]);
        }
        if (sz(down) >= 3 and on_segment(down.back(), down[1], down[0]))
        {
            down[0] = down.back();
            down.pop_back();
        }
        pts = down;
    }
    return pts;
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

ld area_polygon(vector<pt> p)
{
    ld area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++)
    {
        area += cross(p[i], p[(i + 1) % n]);
    }
    return abs(area);
}

// true if P at least as high as A (blue part)
bool above(pt a, pt p)
{
    return p.y >= a.y;
}
// check if [PQ] crosses ray from A
/**
 * @brief Determines if the directed segment pq crosses the horizontal ray to the right of point a.
 *
 * This function checks whether the segment from point p to point q crosses the horizontal ray
 * extending to the right from point a. It uses the helper functions `above` and `orient`:
 * - `above(a, p)` returns whether point p is above point a.
 * - `orient(a, p, q)` returns the orientation of the triplet (a, p, q).
 *
 * @param a The reference point from which the ray is cast.
 * @param p The first endpoint of the segment.
 * @param q The second endpoint of the segment.
 * @return true if the segment pq crosses the ray to the right of a, false otherwise.
 */
bool crossesRay(pt a, pt p, pt q)
{
    return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
}

int in_polygon(vector<pt> p, pt a, bool strict = true)
{
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++)
    {
        if (on_segment(p[i], p[(i + 1) % n], a))
            return 2;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}

ld polygon_cut(const vector<pt> &p, const line &l)
{
    vector<pt> on_left;
    int n = sz(p);
    for (int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n;
        if (l.side(p[i]) > 0)
        {
            on_left.push_back(p[i]);
        }
        pt out;
        // ccw(p[i],p[j],a) * ccw(p[i],p[j],b) < 0
        if (inter(l, line(p[i], p[j]), out))
        {
            if (on_segment(p[i], p[j], out))
            {
                on_left.push_back(out);
            }
        }
    }
    if (sz(on_left) < 3)
    {
        return 0.0;
    }
    on_left = convex_hull(on_left);
    return area_polygon(on_left);
}

ld polygon_diameter(const vector<pt> &p)
{
    int n = sz(p);
    ld res = 0;
    int last = 0;
    for (int i = 0; i < n; ++i)
    {
        while (true)
        {
            int nxt = (last + 1) % n;
            ld a = abs(p[i] - p[last]);
            ld b = abs(p[i] - p[nxt]);
            if (dcmp(b, a) >= 0)
            {
                res = max(res, b);
                last = nxt;
            }
            else
            {
                res = max(res, a);
                break;
            }
        }
    }
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

// struct cmpX
// {
//     bool operator()(pt a, pt b)
//     {
//         return make_pair(a.x, a.y) < make_pair(b.x, b.y);
//     }
// };