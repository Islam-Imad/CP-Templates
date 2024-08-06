#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct SPFA // shortest path faster algorithm
{
    const ll INF = 1e18;
    struct edge
    {
        int v;
        ll w;

        edge(int v, ll w)
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

    SPFA(int n)
        : n(n), adj(n)
    {
    }

    void add_edge(int u, int v, ll w, bool directed = true)
    {
        adj[u].push_back(edge(v, w));
        if (!directed)
            adj[v].push_back(edge(u, w));
    }

    void calc(int src)
    {
        dist.assign(n, INF);
        queue<int> q;
        vector<int> cnt(n), in_queue(n);
        dist[src] = 0;
        q.push(src);
        in_queue[src] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            in_queue[u] = 0;
            for (auto e : adj[u])
            {
                if (dist[u] + e.w < dist[e.v])
                {
                    dist[e.v] = dist[u] + e.w;
                    if (!in_queue[e.v])
                    {
                        q.push(e.v);
                        in_queue[e.v] = 1;
                        if (++cnt[e.v] >= n)
                        {
                            neg_cycle = true;
                            return;
                        }
                    }
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