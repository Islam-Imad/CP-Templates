#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
struct centroid_decomposition // time complexity O(nlogn)
{
    int n;
    vector<int> sz;
    vector<int> par;
    vector<bool> vis;
    vector<vector<int>> adj;
    vector<int> dist;
    centroid_decomposition(int n)
    {
        this->n = n;
        adj.resize(n + 1);
        sz.resize(n + 1);
        vis.resize(n + 1);
        par.resize(n + 1);
    }
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int get_subtree_size(int u, int p)
    {
        sz[u] = 1;
        for (auto v : adj[u])
        {
            if (v == p || vis[v])
                continue;
            sz[u] += get_subtree_size(v, u);
        }
        return sz[u];
    }
    int get_centroid(int u, int p, int tree_size)
    {
        for (auto v : adj[u])
        {
            if (v == p || vis[v])
                continue;
            if (sz[v] * 2 > tree_size)
                return get_centroid(v, u, tree_size);
        }
        return u;
    }
    void decompose(int u, int p)
    {
        int tree_size = get_subtree_size(u, p);
        int centroid = get_centroid(u, p, tree_size);
        vis[centroid] = true;
        par[centroid] = p;
        for (auto v : adj[centroid])
        {
            if (vis[v])
                continue;
            decompose(v, centroid);
        }
    }
};



void solve(){
    
}

int main()
{
ios_base::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin>>tc;
    for(int i=1;i<=tc;++i){
        solve();
    }
}