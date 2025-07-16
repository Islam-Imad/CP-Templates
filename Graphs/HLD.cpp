#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

/*

@Poroblems [
    https://www.hackerrank.com/challenges/subtrees-and-paths/problem
    ]

*/

const ll DEFAULT = 0;   // Replace with appropriate default value
const ll NO_UPDATE = 0; // Replace with appropriate no update value

struct node
{
    ll value;
    ll lazy;
    node(ll value = DEFAULT, ll lazy = NO_UPDATE) : value(value), lazy(lazy) {}
};

node merge(const node a, const node &b)
{
    return node(max(a.value, b.value), NO_UPDATE);
}

class SegmentTree
{
private:
#define lc(id) (2 * id)
#define rc(id) (2 * id + 1)
#define mid(left, right) ((left + right) / 2)

    int size;
    vector<node> seg_tree;

    void Propogate(int id, int l, int r)
    {
        if (seg_tree[id].lazy != NO_UPDATE)
        {
            seg_tree[id].value += seg_tree[id].lazy;
            if (l != r)
            {
                seg_tree[lc(id)].lazy += seg_tree[id].lazy;
                seg_tree[rc(id)].lazy += seg_tree[id].lazy;
            }
            seg_tree[id].lazy = NO_UPDATE;
        }
    }

    void Build(int id, int l, int r, const vector<ll> &arr)
    {
        if (l == r)
        {
            seg_tree[id].value = arr[l]; // edit this line (base zero or base one)
            return;
        }
        Build(lc(id), l, mid(l, r), arr);
        Build(rc(id), mid(l, r) + 1, r, arr);
        seg_tree[id] = merge(seg_tree[lc(id)], seg_tree[rc(id)]);
    }

    void Update(int id, int l, int r, int ul, int ur, ll val)
    {
        Propogate(id, l, r);
        if (l > ur || r < ul)
            return;
        if (l >= ul && r <= ur)
        {
            seg_tree[id].lazy += val;
            Propogate(id, l, r);
            return;
        }
        Update(lc(id), l, mid(l, r), ul, ur, val);
        Update(rc(id), mid(l, r) + 1, r, ul, ur, val);
        seg_tree[id] = merge(seg_tree[lc(id)], seg_tree[rc(id)]);
    }

    void Update(int id, int l, int r, int pos, ll val)
    {
        Propogate(id, l, r);
        if (l == r)
        {
            seg_tree[id].value += val;
            return;
        }
        if (pos <= mid(l, r))
            Update(lc(id), l, mid(l, r), pos, val);
        else
            Update(rc(id), mid(l, r) + 1, r, pos, val);
        seg_tree[id] = merge(seg_tree[lc(id)], seg_tree[rc(id)]);
    }

    node Query(int id, int l, int r, int ql, int qr)
    {
        Propogate(id, l, r);
        if (l > qr || r < ql)
            return node(-1e18, 0);
        if (l >= ql && r <= qr)
            return seg_tree[id];
        return merge(Query(lc(id), l, mid(l, r), ql, qr), Query(rc(id), mid(l, r) + 1, r, ql, qr));
    }

public:
    SegmentTree() = default;
    void init(int size, const vector<ll> &arr = {})
    {
        this->size = size;
        seg_tree.assign(4 * (size + 1), node());
        if (!arr.empty())
            Build(1, 1, size, arr);
    }

    void Update(int l, int r, ll val)
    {
        Update(1, 1, size, l, r, val);
    }

    void Update(int pos, ll val)
    {
        Update(1, 1, size, pos, val);
    }

    node Query(int l, int r)
    {
        return Query(1, 1, size, l, r);
    }
};

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

    SegmentTree seg;

    // segment Tree

    HLD(int size)
        : n(size + 1), sz(size + 1), par(size + 1), depth(size + 1), root(size + 1), pos(size + 1), adj(size + 1), val(size + 1)
    {
        seg.init(n);
    }
    // UTILITY FUNCTIONS
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void reorder(int &u, int &v) const
    {
        if (depth[root[u]] < depth[root[v]])
            swap(u, v);
    }

    // HLD FUNCTIONS
    void build()
    {
        dfs_sz(1, 0), dfs_hld(1, 0, 1);
    }
    void dfs_sz(int u, int p)
    {
        sz[u] = 1;
        for (auto &v : adj[u])
        {
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

    void dfs_hld(int u, int p, int h)
    {
        root[u] = h;
        pos[u] = ++time;
        update(u, val[u]);
        // seg.update(pos[u], val[u]);
        for (auto &v : adj[u])
        {
            if (v == p)
                continue;
            dfs_hld(v, u, (v == adj[u][0] ? h : v));
        }
    }

    // QUERY FUNCTIONS
    int lca(int u, int v) const
    {
        while (root[u] != root[v])
        {
            reorder(u, v);
            u = par[root[u]];
        }
        if (depth[u] < depth[v])
            swap(u, v);
        return v;
    }

    int query(int u, int v)
    {
        ll res = 0;
        while (root[u] != root[v])
        {
            reorder(u, v);
            res = max(res, seg.Query(pos[root[u]], pos[u]).value);
            u = par[root[u]];
        }
        if (depth[u] > depth[v])
            swap(u, v);
        res = max(res, seg.Query(pos[u], pos[v]).value);
        return res;
    }

    void update(int u, int val)
    {
        seg.Update(pos[u], val);
    }

    void update_subtree(int u, int val)
    {
        seg.Update(pos[u], pos[u] + sz[u] - 1, val);
    }

    int dist(int u, int v) const
    {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};

void solve()
{
    int n, q;
    cin >> n;
    HLD hld(n);
    for (int i = 1; i <= n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }
    hld.build();
    cin >> q;
    while (q--)
    {
        string op;
        cin >> op;
        if (op == "add")
        {
            int u, val;
            cin >> u >> val;
            hld.update(u, val);
        }
        else
        {
            int u, v;
            cin >> u >> v;
            cout << hld.query(u, v) << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef LOCAL_IO
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin>>tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}
