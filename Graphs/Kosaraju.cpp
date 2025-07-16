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

    void print()
    {
        vector<vector<int>> components(ncc);
        for (int i = 0; i < n; ++i)
        {
            components[comp[i]].push_back(i);
        }
        cout << ncc << '\n';
        for (int i = 0; i < ncc; ++i)
        {
            // cout << "Component " << i << ": ";
            cout << components[i].size() << " ";
            for (int v : components[i])
                cout << v << " ";
            cout << '\n';
        }
    }
};

int main()
{
}