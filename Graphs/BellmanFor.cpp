#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct Bellman_Ford
{
    const ll INF = 1e18;
    struct edge
    {
        int v, w;

        edge(int v, int w)
            : v(v), w(w)
        {
        }

        bool operator<(const edge &e) const
        {
            return w < e.w;
        }
    };
    int n;
    bool neg_cycle = false;
    vector<vector<edge>> adj;
    vector<ll> dist;

    Bellman_Ford(int n)
        : n(n), adj(n)
    {
    }

    void add_edge(int u, int v, int w, bool directed = true)
    {
        adj[u].push_back(edge(v, w));
        if (!directed)
            adj[v].push_back(edge(u, w));
    }

    void bellman_ford(int src)
    {
        dist.assign(n, INF);
        dist[src] = 0;
        for (int i = 1; i < n; ++i)
        {
            for (int u = 0; u < n; ++u)
            {
                for (auto e : adj[u])
                {
                    if (dist[u] + e.w < dist[e.v])
                        dist[e.v] = dist[u] + e.w;
                }
            }
        }

        for (int u = 0; u < n; ++u)
        {
            for (auto e : adj[u])
            {
                if (dist[u] + e.w < dist[e.v])
                {
                    neg_cycle = true;
                    return;
                }
            }
        }
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