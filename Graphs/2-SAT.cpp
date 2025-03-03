#include <bits/stdc++.h>
using namespace std;

struct Kosaraju
{
    int n;
    int ncc = -1;
    vector<vector<int>> adj, radj;
    vector<int> order, comp;
    vector<bool> vis;

    Kosaraju(int n) : n(n), adj(n), radj(n), comp(n), vis(n)
    {
        adj.shrink_to_fit();
        radj.shrink_to_fit();
        comp.shrink_to_fit();
        vis.shrink_to_fit();
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    void dfs1(int u)
    {
        vis[u] = true;
        for (int v : adj[u])
            if (!vis[v])
                dfs1(v);
        order.push_back(u);
    }

    void dfs2(int u, int color)
    {
        comp[u] = color;
        for (int v : radj[u])
            if (comp[v] == -1)
                dfs2(v, color);
    }

    int build()
    {
        vis.assign(n, false);
        for (int i = 0; i < n; ++i)
            if (!vis[i])
                dfs1(i);

        reverse(order.begin(), order.end());

        fill(comp.begin(), comp.end(), -1);
        int color = 0;
        for (int u : order)
            if (comp[u] == -1)
                dfs2(u, color++);
        return ncc = color;
    }
};

struct TwoSat
{
    int n;
    Kosaraju ks;
    vector<bool> ans;

    TwoSat(int n) : n(n), ks(2 * n), ans(n) {}

    void add_clause(int u, bool fu, int v, bool fv)
    {
        ks.add_edge(2 * u + !fu, 2 * v + fv);
        ks.add_edge(2 * v + !fv, 2 * u + fu);
    }

    bool satisfiable()
    {
        ks.build();
        for (int i = 0; i < n; ++i)
            if (ks.comp[2 * i] == ks.comp[2 * i + 1])
                return false;
        for (int i = 0; i < n; ++i)
            ans[i] = ks.comp[2 * i] < ks.comp[2 * i + 1];
        return true;
    }
};

int main()
{
}
