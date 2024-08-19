#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct DFS
{
    const int LG = 21;
    int n;
    int timer;
    vector<vector<int>> adj;
    vector<int> vis;
    vector<int> parent;
    vector<int> in;
    vector<int> out;
    vector<int> depth;
    vector<int> subtree;
    vector<int> color;

    vector<vector<int>> up;

    DFS(int n) : n(n)
    {
        adj.resize(n + 1);
        vis.resize(n + 1);
        parent.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
        depth.resize(n + 1);
        subtree.resize(n + 1);
        color.resize(n + 1);
        timer = 0;
        up.assign(n + 1, vector<int>(LG));
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
    }


    bool dfs()
    {
        for (int i = 1; i <= n; ++i)
        {
            vis[i] = 0;
        }
        timer = 0;
        bool ok = true;
        for (int i = 1; i <= n; ++i)
        {
            if (!vis[i])
            {
                ok &= dfs_visit(i);
            }
        }
        return ok;
    }

    bool dfs_visit(int u, int p = 0)
    {
        // lca
        up[u][0] = p;
        for (int i = 1; i < LG; ++i)
            up[u][i] = up[up[u][i - 1]][i - 1];

        timer += 1;
        in[u] = timer;
        vis[u] = 1;
        subtree[u] = 1;
        bool res = true;
        for (auto v : adj[u])
        {
            if (!vis[v])
            {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                color[v] = 1 - color[u];
                res &= dfs_visit(v, u);
                subtree[u] += subtree[v];
            }
            else if (color[v] == color[u])
            {
                res = false;
            }
        }
        timer += 1;
        out[u] = timer;
        return res;
    }

    bool is_parent(int u, int v)
    {
        return in[u] <= in[v] && out[u] >= out[v];
    }

    int get_kth_ancestor(int u, int k)
    {
        for (int i = LG - 1; i >= 0; --i)
        {
            if (k & (1 << i))
            {
                u = up[u][i];
            }
        }
        return u;
    }

    int get_lca(int u, int v)
    {
        if (is_parent(u, v))
            return u;
        if (is_parent(v, u))
            return v;
        for (int i = LG - 1; i >= 0; --i)
        {
            if (up[u][i] == 0)
                continue;
            if (!is_parent(up[u][i], v))
            {
                u = up[u][i];
            }
        }
        return up[u][0];
    }
};

void solve()
{
    
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}