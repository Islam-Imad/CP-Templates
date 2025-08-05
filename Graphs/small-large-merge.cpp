#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

/*
F[i] = sigma {d | i} G(d)
G[i] = sigma {d | i} mob(d) * F(i/d)
G[i] = sigma {d | i} mob(i/d) * F(d)
*/

const int N = 1e6 + 5;
const int mod = 1e9 + 7;

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

int add_mod(int a, int b)
{
    return (a + b) % mod;
}

int sub_mod(int a, int b)
{
    return (a - b + mod) % mod;
}

int mul_mod(int a, int b)
{
    return (1LL * a * b) % mod;
}

int prime[N];
int mob[N];
int pw[N];
int we[N];

vector<int> dv[N];

void sieve()
{
    pw[0] = 1;
    for (int i = 1; i < N; ++i)
    {
        prime[i] = i;
        mob[i] = 1;
        pw[i] = mul_mod(2, pw[i - 1]);
    }
    prime[1] = 0;
    for (int i = 2; i < N; ++i)
    {
        if (prime[i] == i) // i is prime
        {
            for (int j = i; j < N; j += i)
            {
                prime[j] = min(prime[j], i);
                mob[j] *= -1;
                if ((j / i) % i == 0)
                {
                    mob[j] = 0;
                }
            }
        }
        mob[i] = add_mod(mob[i], mod);
    }
    for (int i = 1; i < N; ++i)
    {
        for (int j = i; j < N; j += i)
        {
            dv[j].push_back(i);
        }
        if (prime[i] == i)
        {
            for (int j = i; j < N; j += i)
            {
                we[j] = add_mod(we[j], mob[j / i]);
            }
        }
    }
}

// void add(int node, int val, int count)
// {
//     for (int d : dv[val])
//     {
//         int add_value = add(count, mul(dp[node][d], count));
//         res[node] = add(res[node], mul(we[d], add_value));
//         // dp[node][d] = add(add(dp[node][d], count), mul(dp[node][d], count));
//         dp[node][d] = add(dp[node][d], add_value);
//     }
// }

struct small_large_merge
{
    int n;
    vector<int> tin;
    vector<int> tout;
    vector<int> siz;
    vector<int> euler;
    vector<int> val;
    vector<int> ans;
    vector<vector<int>> adj;

    small_large_merge(int n) : n(n), tin(n + 1), tout(n + 1), siz(n + 1), val(n + 1), adj(n + 1)
    {
        euler.reserve(2 * n + 2);
        ans.resize(n + 1);
        freq.assign(1e6 + 2, 0);
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void set_val(int u, int value)
    {
        val[u] = value;
    }

    void euler_tour(int u, int p)
    {
        tin[u] = euler.size();
        euler.push_back(u);
        siz[u] = 1;

        for (int v : adj[u])
        {
            if (v != p)
            {
                euler_tour(v, u);
                siz[u] += siz[v];
            }
        }
    }

    vector<int> freq;
    int res = 0;
    void remove(int u)
    {
        for (int d : dv[val[u]])
        {
            int rem_value = pw[freq[d] - 1];
            res = sub_mod(res, mul_mod(we[d], rem_value));
            freq[d]--;
        }
    }

    void add(int u)
    {
        for (int d : dv[val[u]])
        {
            int add_value = pw[freq[d]];
            res = add_mod(res, mul_mod(we[d], add_value));
            freq[d]++;
        }
    }

    void calc(int u)
    {
        ans[u] = res;
    }

    void dfs(int u, int p, bool keep)
    {
        int heavy_child = -1, max_size = -1;
        for (int v : adj[u])
        {
            if (v != p && siz[v] > max_size)
            {
                max_size = siz[v];
                heavy_child = v;
            }
        }
        for (int v : adj[u])
        {
            if (v != p && v != heavy_child)
            {
                dfs(v, u, false);
            }
        }
        if (heavy_child != -1)
        {
            dfs(heavy_child, u, true);
        }

        add(u);

        for (int v : adj[u])
        {
            if (v != p && v != heavy_child)
            {
                int subtree_size = siz[v];
                for (int i = 0; i < subtree_size; ++i)
                {
                    int node = euler[tin[v] + i];
                    add(node);
                }
            }
        }
        calc(u);
        if (keep == false)
        {
            int subtree_size = siz[u];
            for (int i = 0; i < subtree_size; ++i)
            {
                int node = euler[tin[u] + i];
                remove(node);
            }
        }
    }
};

void solve()
{
    sieve();
    int n;
    cin >> n;
    small_large_merge slm(n);
    for (int i = 0; i < n; ++i)
    {
        int val;
        cin >> val;
        slm.set_val(i + 1, val);
    }
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        slm.add_edge(u, v);
    }
    slm.euler_tour(1, 0);
    slm.dfs(1, 0, false);
    for (int i = 1; i <= n; ++i)
    {
        cout << slm.ans[i] << " ";
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
        solve();
    }
}