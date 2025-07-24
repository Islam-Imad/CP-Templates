#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

struct virtual_tree
{
    int n;
    int dfs_time;
    int k;
    vector<int> in, out;
    vector<int> depth;
    vector<vector<ll>> lv;
    vector<vector<int>> adj;
    vector<vector<int>> at_dep;
    vector<vector<pair<int, int>>> vadj;
    vector<vector<int>> up;

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
        adj.assign(n + 1, vector<int>());
        at_dep.assign(n + 1, vector<int>());
        vadj.assign(n + 1, vector<pair<int, int>>());
        up.assign(n + 1, vector<int>(k + 1));
        lv.assign(n + 1, vector<ll>(k + 1));
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p = 0)
    {
        in[u] = dfs_time++;
        up[u][0] = p;
        depth[u] = depth[p] + 1;
        at_dep[depth[u]].push_back(u);
        for (int i = 1; i <= k; ++i)
        {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (int v : adj[u])
        {
            if (v != p)
            {
                dfs(v, u);
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
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
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
            vadj[lca_uv].push_back({v, depth[v] - depth[lca_uv]});
        }
        return res;
    }

    void build_val()
    {
        for (int val = n; val >= 1; --val)
        {
            for (int i = 1; i <= k and val + (1 << (i - 1)) <= n; ++i)
            {
                lv[val][i] = min(lv[val][i - 1], lv[val + (1 << (i - 1))][i - 1]);
            }
        }
    }

    ll get_val(int dep, int mvp = 0)
    {
        ll res = 1e18;
        mvp += 1;
        mvp = min(mvp, n - dep + 1);
        for (int i = 0; i <= k; ++i)
        {
            if (mvp & (1 << i))
            {
                res = min(res, lv[dep][i]);
                dep += (1 << i);
            }
        }
        return res;
    }
};

/*
https://atcoder.jp/contests/abc340/tasks/abc340_g
https://codeforces.com/gym/104128/problem/E
*/

void solve()
{
    int n, cd;
    cin >> n;
    virtual_tree vt(n, 20);
    for (int i = 1; i <= n; ++i)
    {
        cin >> vt.lv[i][0];
    }

    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        vt.add_edge(u, v);
    }
    vt.dfs(1);
    vt.build_val();

    function<ll(int, int)> calc = [&](int u, int p) -> ll
    {
        if (vt.depth[u] == cd)
        {
            return vt.get_val(1, cd - 1);
        }
        ll res = 0;
        for (auto &[v, d] : vt.vadj[u])
        {
            if (v == p)
                continue;
            res += calc(v, u);
        }
        return min(res, vt.get_val(1 + cd - vt.depth[u], vt.depth[u] - 1));
    };
    ll tot = 0;
    for (int level = 1; level <= n; ++level)
    {
        auto &nodes = vt.at_dep[level];
        nodes = vt.pair_lcas(nodes);
        cd = level;
        if (nodes.empty())
        {
            break;
        }
        tot += calc(nodes[0], 0);
    }
    cout << tot << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef LOCAL_IO
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    cin >> tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}