
#include <bits/stdc++.h>
using namespace std;
const long double OO = 4e9;
#define ll long long int
#define ld long double
#define X real()
#define Y imag()
#define EPS 1e-9
#define PI acos(-1)
#define vec(a, b) (b - a)
#define dotp(a, b) (conj(a) * b).real()
#define crossp(a, b) (conj(a) * b).imag()
#define same(a, b) (abs(a - b) < EPS)
#define normalize(a) (a / abs(a))
#define rotateA(p, ang, about) ((p - about) * exp(P(0, ang)) + about)
#define rotate0(p, ang) (p * exp(P(0, ang)))
#define reflect0(v, m) (conj(v / m) * m)
#define reflectA(v, a, m) (reflect0(vec(m, v), vec(m, rotateA(v, a, m)) + m))
#define length(v) (hypot(v.Y, v.X))

typedef complex<ld> P;

int dcmp(ld x, ld y)
{
    if (fabs(x - y) < 1e-9)
        return 0;
    return x < y ? -1 : 1;
}

P pointToLine(P a, P b, P c)
{
    // answer is the projection of point c on line ab
    return a + ((dotp(vec(a, b), vec(a, c)) / norm(vec(a, b))) * (vec(a, b)));
}

ld from_deg_to_rad(ld deg)
{
    ld ret = deg * PI / 180.0;
    if (ret < 0)
        ret += 2 * PI;
    return ret;
}

ld from_rad_to_deg(ld rad)
{
    ld ret = rad * 180.0 / PI;
    if (ret < 0)
        ret += 360;
    return ret;
}

ld distToLine(P a, P b, P c)
{
    return abs(crossp(vec(a, b), vec(a, c))) / abs(b - a);
}

bool isCollinear(P a, P b, P c)
{
    return dcmp(crossp(vec(a, b), vec(a, c)), 0) == 0;
}

bool isPointOnRay(P a, P b, P c)
{
    if (!isCollinear(a, b, c))
        return false;
    return dcmp(dotp(vec(a, b), vec(a, c)), 0) == 1;
    // return same(normalize(b - a), normalize(c - a));
}

bool isPointOnSegment(P a, P b, P c)
{
    // ld d1 = abs(b - a), d2 = abs(c - a);
    // return same(d1+d2,abs(a-b));
    return isPointOnRay(a, b, c) && isPointOnRay(b, a, c);
}

ld CircleArea(ld r)
{
    return PI * r * r;
}

// Triangle Area two sides and angle between them
ld TriangleArea(ld a, ld b, ld angle)
{
    return 0.5 * a * b * sin(angle);
}
// Triangle Area three sides
// ld TriangleArea(ld a, ld b, ld c){
//     ld s = (a + b + c) / 2;
//     return sqrt(s * (s - a) * (s - b) * (s - c));
// }
// Triangle Area three points
ld TriangleArea3(P a, P b, P c)
{
    return abs(crossp(vec(a, b), vec(a, c))) / 2.0;
}

struct cmpX
{
    bool operator()(const P &a, const P &b)
    {
        if (dcmp(a.X, b.X) != 0)
            return dcmp(a.X, b.X) < 0;
        return dcmp(a.Y, b.Y) < 0;
    }
};

struct cmpY
{
    bool operator()(const P &a, const P &b) const
    {
        if (dcmp(a.Y, b.Y) != 0)
            return dcmp(a.Y, b.Y) < 0;
        return dcmp(a.X, b.X) < 0;
    }
};

pair<P, P> closest_pair(vector<P> v)
{
    sort(v.begin(), v.end(), cmpX());
    set<P, cmpY> box;
    double best = OO;
    pair<P, P> best_pair;
    for (int i = 0, j = 0; i < v.size(); i++)
    {
        while (j < i && v[i].X - v[j].X > best)
            box.erase(v[j++]);
        auto l = box.lower_bound(P(-OO, v[i].Y - best));
        auto r = box.upper_bound(P(-OO, v[i].Y + best));
        for (auto it = l; it != r; it++)
        {
            double d = length(vec(v[i], *it));
            if (d < best)
                best = d, best_pair = {v[i], *it};
        }
        box.insert(v[i]);
    }
    return best_pair;
}

void solve()
{
    int n;
    cin >> n;
    vector<P> v(n);
    for (int i = 0; i < n; ++i)
    {
        ll x, y;
        cin >> x >> y;
        v[i] = P(y, x);
    }
    pair<P, P> res = closest_pair(v);
    // cout << res.first.Y << ' ' << res.first.X << ' ' << res.second.Y << ' ' << res.second.X << '\n';
    cout << (ll)(res.first.X - res.second.X) * (ll)(res.first.X - res.second.X) + (ll)(res.first.Y - res.second.Y) * (ll)(res.first.Y - res.second.Y) << '\n';
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
/*
P p = {1 , 1};
p *= polar(1.0, from_deg_to_rad(90)); // polar(r, theta) = r * (cos(theta) + i * sin(theta))
cout << "Real part: " << p.real() << " Imaginary part: " << p.imag() << endl;
cout << "Magnitude: " << abs(p)  << '\n'; // abs = sqrt(x^2 + y^2)
cout << "Argument: " << arg(p) << '\n'; // arg = atan2(y, x)
cout << "Conjugate: " << conj(p) << '\n'; // conjugate = x - iy
cout << "Polar: " << polar(abs(p), arg(p)) << '\n'; // polar(r, theta)
cout << "Norm: " << norm(p) << '\n'; // NORM = x^2 + y^2


cross product = a.x * b.y - a.y * b.x = |a| * |b| * sin(theta)
dot product = a.x * b.x + a.y * b.y = |a| * |b| * cos(theta)

// ans triangle the length of the hypotenuse is the magnitude of the vector
*/
