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
const ld INF = 1e18;

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

istream &operator>>(istream &is, pt &p)
{
    return is >> p.x >> p.y;
}

ostream &operator<<(ostream &os, const pt &p)
{
    return os << p.x << " " << p.y;
}

struct cmpX
{
    bool operator()(const pt &a, const pt &b)
    {
        if (dcmp(a.x, b.x) != 0)
            return dcmp(a.x, b.x) < 0;
        return dcmp(a.y, b.y) < 0;
    }
};

struct cmpY
{
    bool operator()(const pt &a, const pt &b) const
    {
        if (dcmp(a.y, b.y) != 0)
            return dcmp(a.y, b.y) < 0;
        return dcmp(a.x, b.x) < 0;
    }
};

pair<pt, pt> closes_pair(vector<pt> v)
{
    pair<pt, pt> res;
    int n = v.size();
    sort(v.begin(), v.end(), cmpX());
    set<pt, cmpY> s;
    ld best = INF;
    for (int i = 0, j = 0; i < n; ++i)
    {
        while (j < i and v[i].x - v[j].x > best)
        {
            s.erase(v[j]);
            j++;
        }
        auto l = s.lower_bound({-INF, v[i].y - best});
        auto r = s.upper_bound({-INF, v[i].y + best});
        for (auto it = l; it != r; ++it)
        {
            ld d = abs(v[i] - *it);
            if (d < best)
            {
                best = d;
                res = {v[i], *it};
            }
        }
        s.insert(v[i]);
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<pt> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    pair<pt, pt> res = closes_pair(v);
    // cout << res.X << ' ' << res.Y << '\n';
    cout << fixed << setprecision(10) << abs(res.X - res.Y);
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