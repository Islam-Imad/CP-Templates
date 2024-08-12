#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct DFS
{
    int n;
    int timer;
    vector<vector<int>> adj;
    vector<int> vis;
    vector<int> par;
    vector<int> in;
    vector<int> out;
    vector<int> depth;
    vector<int> subtree;
    vector<int> color;

    DFS(int n) : n(n)
    {
        adj.resize(n + 1);
        vis.resize(n + 1);
        par.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
        depth.resize(n + 1);
        subtree.resize(n + 1);
        color.resize(n + 1);
        timer = 0;
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

    bool dfs_visit(int u)
    {
        timer += 1;
        in[u] = timer;
        vis[u] = 1;
        subtree[u] = 1;
        bool res = true;
        for (auto v : adj[u])
        {
            if (!vis[v])
            {
                par[v] = u;
                depth[v] = depth[u] + 1;
                color[v] = 1 - color[u];
                res &= dfs_visit(v);
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