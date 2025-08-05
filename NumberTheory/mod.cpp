#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const ll mod = 1e9 + 7;

const int N = 1e6 + 5;

ll fac[N], ifac[N];

ll modpow(ll base, ll exp)
{
    base %= mod;
    ll res = 1;
    while (exp)
    {
        if (exp & 1)
            res = res * base % mod;
        base = base * base % mod, exp >>= 1;
    }
    return res;
}

ll add_mod(ll a, ll b)
{
    return (a + b) % mod;
}

ll sub_mod(ll a, ll b)
{
    return (a - b + mod) % mod;
}

ll mul_mod(ll a, ll b)
{
    return (a * b) % mod;
}

ll inv_mod(ll a)
{
    return modpow(a, mod - 2);
}

ll div_mod(ll a, ll b)
{
    return mul_mod(a, inv_mod(b));
}

void precompute()
{
    fac[0] = 1;
    for (int i = 1; i < N; ++i)
        fac[i] = mul_mod(fac[i - 1], i);
    ifac[N - 1] = inv_mod(fac[N - 1]);
    for (int i = N - 2; i >= 0; --i)
        ifac[i] = mul_mod(ifac[i + 1], i + 1);
}

ll nCr(int n, int r)
{
    if (n < r || r < 0)
        return 0;
    return mul_mod(fac[n], mul_mod(ifac[r], ifac[n - r]));
}

ll nPr(int n, int r)
{
    if (n < r || r < 0)
        return 0;
    return mul_mod(fac[n], ifac[n - r]);
}

ll catalan(int n)
{
    if (n == 0)
        return 1;
    return div_mod(nCr(2 * n, n), n + 1);
}

ll starts_bars(ll balls, ll boxes)
{
    return nCr(balls + boxes - 1, boxes - 1);
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