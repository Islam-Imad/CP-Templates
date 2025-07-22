#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

auto start_time = chrono::high_resolution_clock::now();

void start_timer()
{
    start_time = chrono::high_resolution_clock::now();
}

double get_elapsed_time()
{
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    return duration.count() / 1000.0; // Return in milliseconds
}

ll ceil(ll a, ll b)
{
    ll sign = (a < 0) ^ (b < 0) ? -1 : 1;
    a = abs(a), b = abs(b);
    if (sign == -1)
    {
        return -(a / b);
    }
    return (a + b - 1) / b;
}

ll floor(ll a, ll b)
{
    ll sign = (a < 0) ^ (b < 0) ? -1 : 1;
    a = abs(a), b = abs(b);
    if (sign == -1)
    {
        return -((a + b - 1) / b);
    }
    return a / b;
}

ll gcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

/*
_x = x - k * (b / g)
_y = y + k * (a / g)


*/
bool LDE(ll a, ll b, ll c, ll &x, ll &y, ll &x_up, ll &y_up)
{

    ll g = gcd(a, b, x, y);
    if (c % g != 0)
    {
        return false;
    }
    x *= c / g;
    y *= c / g;
    x_up = b / g;
    y_up = a / g;
    return true;
}

ll modInv(ll a, ll m)
{
    ll x, y;
    if (gcd(a, m, x, y) != 1)
    {
        return -1; // Inverse doesn't exist
    }
    return (x % m + m) % m; // Ensure positive result
}

ll minAbs(ll a, ll b, ll c)
{
    ll x, y, x_up, y_up;
    if (!LDE(a, b, c, x, y, x_up, y_up))
    {
        return -1; // No solution
    }
    ll cost = 1e18;
    int vx = (x) / x_up;
    int vy = (-y + y_up - 1) / y_up;
    // cout << "vx: " << vx << ", vy: " << vy << '\n';
    auto check = [&](int k)
    {
        ll nx = x - k * x_up;
        ll ny = y + k * y_up;
        if (nx >= 0 && ny >= 0)
        {
            ll cost_now = nx + ny;
            if (cost_now < cost)
            {
                cost = cost_now;
            }
        }
    };
    for (int i = -5; i <= 5; ++i)
    {
        check(vx + i);
        check(vy + i);
    }
    return cost == 1e18 ? -1 : cost;
}

void solve()
{
    ll c;
    cin >> c;
    ll ca, a, cb, b;
    cin >> ca >> a >> cb >> b;
    ll x, y, xup, yup;
    bool flag = LDE(a, b, c, x, y, xup, yup);
    if (flag)
    {
        ll vx = floor(x, xup);
        ll vy = ceil(-y, yup);
        cout << vx << ' ' << vy << '\n';
        for (int k = vy - 1; k <= vx + 1; ++k)
        {
            ll nx = x - k * xup;
            ll ny = y + k * yup;
            cout << nx << ' ' << ny << '\n';
        }
    }
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
        start_timer();
        solve();
        double elapsed = get_elapsed_time();
        cerr << "Test case " << i << " completed in " << fixed << setprecision(3) << elapsed << " ms\n";
    }
}

/*

void solve()
{
    ll a, b, c, x, y, x_up, y_up;
    ll ca, cb;
    while (cin >> c && c)
    {
        ll cost = 1e18;
        cin >> ca >> a >> cb >> b;
        bool flag = LDE(a, b, c, x, y, x_up, y_up);
        if (!flag)
        {
            cout << "failed\n";
            continue;
        }
        int vx = (x) / x_up;
        int vy = (-y + y_up - 1) / y_up;
        pair<int, int> res = {-1, -1};
        // cout << vx << ' ' << vy << '\n';
        auto check = [&](int k)
        {
            ll nx = x - k * x_up;
            ll ny = y + k * y_up;
            if (nx >= 0 && ny >= 0)
            {
                ll cost_now = nx * ca + ny * cb;
                if (cost_now < cost)
                {
                    cost = cost_now;
                    res = {nx, ny};
                }
            }
        };
        for (int i = -5; i <= 5; ++i)
        {
            check(vx + i);
            check(vy + i);
        }
        if (res.X == -1 && res.Y == -1)
        {
            cout << "failed\n";
        }
        else
        {
            cout << res.X << " " << res.Y << "\n";
        }
    }
}

*/