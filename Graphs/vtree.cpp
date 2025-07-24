#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#pragma GCC optimize("Ofast,unroll-loops")

struct virtual_tree
{
    int n;
    int dfs_time;
    int k;
    vector<int> in, out;
    vector<int> depth;
    vector<vector<ll>> lv;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> at_dep;
    vector<vector<pair<int, int>>> vadj;
    vector<vector<int>> up;
    vector<int> dis;

    virtual_tree(int n, int k)
    {
        init(n, k);
    }

    virtual_tree() {}

    void init(int n, int k)
    {
        this->n = n;
        this->k = k;
        dfs_time = 0;
        in.assign(n + 1, -1);
        out.assign(n + 1, -1);
        depth.assign(n + 1, 0);
        adj.assign(n + 1, vector<pair<int, int>>());
        vadj.assign(n + 1, vector<pair<int, int>>());
        up.assign(n + 1, vector<int>(k + 1));
        dis.assign(n + 1, 0);
    }

    void add_edge(int u, int v, int d)
    {
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }

    void dfs(int u, int p, int d)
    {
        in[u] = dfs_time++;
        depth[u] = depth[p] + 1;
        up[u][0] = p;
        dis[u] = d + dis[p];
        for (int i = 1; i <= k; ++i)
        {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto [v, d2] : adj[u])
        {
            if (v != p)
            {
                dfs(v, u, d2);
            }
        }
        out[u] = dfs_time++;
    }

    int lca(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);
        for (int i = k; i >= 0; --i)
        {
            if (depth[up[u][i]] >= depth[v])
            {
                u = up[u][i];
            }
        }
        if (u == v)
            return u;
        for (int i = k; i >= 0; --i)
        {
            if (up[u][i] != up[v][i])
            {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
    int dist(int u, int v)
    {
        return dis[u] + dis[v] - 2 * dis[lca(u, v)];
    }

    vector<int> pair_lcas(vector<int> nodes)
    {
        auto cmp = [this](const int &u, const int &v)
        {
            return in[u] < in[v];
        };
        sort(all(nodes), cmp);
        vector<int> res = nodes;
        for (int i = 0; i < sz(nodes) - 1; ++i)
        {
            int u = nodes[i], v = nodes[i + 1];
            int lca_uv = lca(u, v);
            res.push_back(lca_uv);
        }
        sort(all(res), cmp);
        res.erase(unique(res.begin(), res.end()), res.end());
        for (auto &node : res)
        {
            vadj[node].clear();
        }
        for (int i = 0; i < sz(res) - 1; ++i)
        {
            int u = res[i], v = res[i + 1];
            int lca_uv = lca(u, v);
            vadj[lca_uv].push_back({v, dis[v] - dis[lca_uv]});
        }
        return res;
    }
};

/*
https://atcoder.jp/contests/abc340/tasks/abc340_g
https://codeforces.com/gym/104128/problem/E
https://www.hackerrank.com/contests/worldcupsemifinals/challenges/wccity/problem
*/

void solve()
{
    int n, q;
    cin >> n >> q;
    virtual_tree vt(n, 20);
    vector<ll> vis(n + 1, 0);
    vector<ll> dp(n + 1, 0);
    vector<ll> dp2(n + 1, 0);
    vector<ll> dp3(n + 1, 0);
    for (int i = 1; i < n; ++i)
    {
        int u, v, d;
        cin >> u >> v >> d;
        vt.add_edge(u, v, d);
    }
    vt.dfs(1, 0, 0);
    // Example of a lambda function, renamed to avoid conflict with vt.dfs
    function<void(int, int)> print_edges = [&](int u, int p)
    {
        dp2[u] = vis[u];
        dp[u] = 0;
        dp3[u] = 0;
        for (auto [v, d] : vt.vadj[u])
        {
            if (v != p)
            {
                print_edges(v, u);
                ll add = (dp[v] + (dp2[v] * d));
                dp3[u] += ((add * (dp2[u] - vis[u])) + (dp2[v] * dp[u]));
                dp2[u] += dp2[v];
                dp[u] += add;
            }
        }
    };
    while (q--)
    {
        int k = 0;
        cin >> k;
        vector<int> nodes(k);
        for (int i = 0; i < k; ++i)
        {
            cin >> nodes[i];
            vis[nodes[i]] += 1;
        }
        vector<int> lcas = vt.pair_lcas(nodes);
        ll tot = 0;
        print_edges(lcas[0], 0); // Print edges starting from the first LCA
        for (auto &i : lcas)
        {
            tot += dp3[i];
            tot += (vis[i] * dp[i]);
            vis[i] = 0;
        }
        cout << tot << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef LOCAL_IO
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}