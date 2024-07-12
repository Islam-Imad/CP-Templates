/*
    Heavy Light Decomposition
    1. LCA
    2. Query on path
    3. Update on path
    4. Distance between two nodes
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

/*
    Range Query with point update
    (min , max , sum , gcd , ..)
    Time Complexity : O(log(n))
    Space Complexity : O(n)
    1 based indexing

    =>> allow you to update a single element and query on a range
*/

struct HLD
{
    int n;
    int time = 0;

    vector<ll> val;
    vector<int> sz;
    vector<int> pos;
    vector<int> par;
    vector<int> root;
    vector<int> depth;
    vector<vector<int>> adj;
    
    // segment Tree

    HLD(int size)
        : n(size + 1)
        , sz(size + 1)
        , par(size + 1)
        , depth(size + 1)
        , root(size + 1)
        , pos(size + 1)
        , adj(size + 1)
        , val(size + 1){
        // segment Tree
    }
    // UTILITY FUNCTIONS
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void reorder(int &u, int &v) const{
        if (depth[root[u]] < depth[root[v]])
            swap(u, v);
    }

    // HLD FUNCTIONS
    void build(){
        dfs_sz(1, 0),dfs_hld(1, 0, 1);
    }
    void dfs_sz(int u, int p){
        sz[u] = 1;
        for (auto &v : adj[u]){
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            par[v] = u;
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]] || adj[u][0] == p)
            {
                swap(v, adj[u][0]);
            }
        }
    }

    void dfs_hld(int u, int p, int h){
        root[u] = h;
        pos[u] = ++time;
        // seg.update(pos[u], val[u]);
        for (auto &v : adj[u])
        {
            if (v == p)
                continue;
            dfs_hld(v, u, (v == adj[u][0] ? h : v));
        }
    }

    // QUERY FUNCTIONS
    int lca(int u, int v) const{
        while (root[u] != root[v])
        {
            reorder(u, v);
            u = par[root[u]];
        }
        if (depth[u] < depth[v])
            swap(u, v);
        return v;
    }

    ll query(int u, int v){
        ll res = 0;
        while (root[u] != root[v])
        {
            reorder(u, v);
            // res = max(res, seg.Query(pos[root[u]], pos[u]));
            u = par[root[u]];
        }
        if (depth[u] > depth[v])swap(u, v);
        // res = max(res, seg.Query(pos[u], pos[v]));
        return res;
    }

    int dist(int u, int v) const{
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
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
    // cin>>tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}
