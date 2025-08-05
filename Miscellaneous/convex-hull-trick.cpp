#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define sz(x) ((int)(x).size())

const ll is_query = -(1LL << 62);
struct line
{
    ll m, b;
    mutable function<const line *()> succ;
    bool operator<(const line &rhs) const
    {
        if (rhs.b != is_query)
            return m < rhs.m;
        const line *s = succ();
        if (!s)
            return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};

struct dynamic_hull : public multiset<line>
{ // will maintain upper hull for maximum
    const ll inf = LLONG_MAX;
    bool bad(iterator y)
    {
        auto z = next(y);
        if (y == begin())
        {
            if (z == end())
                return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end())
            return y->m == x->m && y->b <= x->b;

        /* compare two lines by slope, make sure denominator is not 0 */
        ll v1 = (x->b - y->b);
        if (y->m == x->m)
            v1 = x->b > y->b ? inf : -inf;
        else
            v1 /= (y->m - x->m);
        ll v2 = (y->b - z->b);
        if (z->m == y->m)
            v2 = y->b > z->b ? inf : -inf;
        else
            v2 /= (z->m - y->m);
        return v1 >= v2;
    }
    void insert_line(ll m, ll b)
    {
        auto y = insert({m, b});
        y->succ = [=]
        { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y))
        {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y)))
            erase(next(y));
        while (y != begin() && bad(prev(y)))
            erase(prev(y));
    }
    ll eval(ll x)
    {
        auto l = *lower_bound((line){x, is_query});
        return l.m * x + l.b;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> b(n);
    vector<ll> s(n);
    vector<ll> dp(n);
    dynamic_hull cht;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i)
    {
        cin >> b[i];
    }
    s[0] = a[0];
    for (int i = 1; i < n; ++i)
    {
        s[i] = s[i - 1] + a[i];
    }
    dp[0] = 0;
    cht.insert_line(0, 0);
    for (int i = 1; i < n; ++i)
    {
        dp[i] = s[i] * b[i] - cht.eval(b[i]);
        cht.insert_line(s[i - 1], -dp[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        cout << dp[i] << ' ';
    }
    cout << '\n';
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

/*
    ll n, c;
    cin >> n >> c;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    vector<ll> dp(n + 1);
    dp[n - 1] = 0;
    dynamic_hull cht;
    cht.insert_line(-(-2ll * a[n - 1]), -(a[n - 1] * a[n - 1]));
    for (int i = n - 2; i >= 0; --i)
    {
        dp[i] = c + a[i] * a[i];
        dp[i] -= cht.eval(a[i]);
        cht.insert_line(-(-2ll * a[i]), -(a[i] * a[i] + dp[i]));
    }
    cout << dp[0] << '\n';
*/