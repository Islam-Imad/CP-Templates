#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

struct seg_node
{
    vector<ll> v;
    seg_node() {}
    seg_node(const vector<ll> &vec) : v(vec) {}
};

int query_node(const seg_node &node, int val)
{
    return upper_bound(all(node.v), val) - node.v.begin();
}

void merge(const seg_node &a, const seg_node &b, seg_node &res)
{
    int n = a.v.size();
    int m = b.v.size();
    int c = n + m;
    res.v.resize(c);
    int i = 0, j = 0, k = 0;
    while (i < n && j < m)
    {
        if (a.v[i] < b.v[j])
            res.v[k++] = a.v[i++];
        else
            res.v[k++] = b.v[j++];
    }
    while (i < n)
        res.v[k++] = a.v[i++];
    while (j < m)
        res.v[k++] = b.v[j++];
}

struct segment_tree
{
    int n;
    vector<seg_node> tree;
    segment_tree(int size) : n(size), tree(4 * size) {}

    void build(vector<ll> &arr)
    {
        build(1, 0, n - 1, arr);
    }
    void build(int node, int start, int end, vector<ll> &arr)
    {
        if (start == end)
        {
            tree[node] = seg_node({arr[start]});
        }
        else
        {
            int mid = (start + end) / 2;
            build(2 * node, start, mid, arr);
            build(2 * node + 1, mid + 1, end, arr);
            merge(tree[2 * node], tree[2 * node + 1], tree[node]);
        }
    }

    int query(int l, int r, ll val)
    {
        return query(1, 0, n - 1, l, r, val);
    }
    int query(int node, int start, int end, int l, int r, ll val)
    {
        if (start > r || end < l)
            return 0; // out of range
        if (start >= l && end <= r)
        {
            return query_node(tree[node], val);
        }
        int mid = (start + end) / 2;
        int left_query = query(2 * node, start, mid, l, r, val);
        int right_query = query(2 * node + 1, mid + 1, end, l, r, val);
        return left_query + right_query;
    }

    int mex(int l, int r)
    {
        int lo = -1, hi = (r - l + 1);
        int ans = -1;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (query(l, r, mid) >= mid + 1)
            {
                ans = mid;
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }
        return ans + 1;
    }
};

void solve()
{
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