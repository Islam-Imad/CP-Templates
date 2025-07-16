#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

ll add_mod(ll a, ll b, ll mod = 1e9 + 7)
{
    return ((a % mod) + (b % mod)) % mod;
}

ll sub_mod(ll a, ll b, ll mod = 1e9 + 7)
{
    return ((a % mod) - (b % mod) + mod) % mod;
}

ll mul_mod(ll a, ll b, ll mod = 1e9 + 7)
{
    return ((a % mod) * (b % mod)) % mod;
}

ll pow_mod(ll a, ll b, ll mod = 1e9 + 7)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        b >>= 1;
    }
    return res;
}

ll inv_mod(ll a, ll mod = 1e9 + 7)
{
    return pow_mod(a, mod - 2, mod);
}

struct HashString
{
    vector<ll> hash;
    vector<ll> power;
    ll mod = 1e9 + 7;
    ll base = 131;

    HashString(ll mod = 1e9 + 7, ll base = 131) : mod(mod), base(base)
    {
    }

    void Hash(const string &s)
    {
        int n = sz(s);
        hash.resize(n + 1, 0);
        power.resize(n + 1, 1);
        for (int i = 0; i < n; ++i)
        {
            hash[i + 1] = add_mod(mul_mod(s[i], power[i], mod), hash[i], mod);
            power[i + 1] = mul_mod(power[i], base, mod);
        }
    }

    ll get_hash(int l, int r)
    {
        // base zero
        if (l > r || l < 0 || r >= sz(hash))
            return 0;
        ll res = sub_mod(hash[r + 1], hash[l], mod);
        res = mul_mod(res, inv_mod(power[l], mod), mod);
        return res;
    }
};

void solve()
{
    string s;
    cin >> s;
    int n = sz(s);
    HashString hs;
    hs.Hash(s);

    vector<int> ans;
    for (int i = 1; i <= n; ++i)
    {
        bool ok = true;
        for (int j = 0; j < n; j += i)
        {
            int r = min(j + i - 1, n - 1);
            int l = j;
            if (hs.get_hash(l, r) != hs.get_hash(0, (r - l)))
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            ans.push_back(i);
        }
    }
    for (auto &x : ans)
    {
        cout << x << " ";
    }
    cout << "\n";
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