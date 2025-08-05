#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int N = 1e5 + 5;
const ll INF = 1e18;

ll a[N];

struct node
{
    ll min_A;
    ll min_B;
    ll min_D;
    ll lazy;
    ll res;
    node() : min_A(0), min_B(INF), min_D(0), lazy(0), res(0) {}
};

node merge(const node &a, const node &b)
{
    node res;
    res.min_A = min(a.min_A, b.min_A);
    res.min_B = min(a.min_B, b.min_B);
    res.min_D = min(a.min_D, b.min_D);
    res.res = min(res.min_A, res.min_B);
    return res;
}

node tree[4 * N];

void build(int id, int l, int r)
{
    if (l == r)
    {
        tree[id].min_A = a[l];
        tree[id].min_B = INF;
        tree[id].min_D = a[l];
        tree[id].lazy = 0;
        tree[id].res = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    tree[id] = merge(tree[2 * id], tree[2 * id + 1]);
}

void push(int id, int l, int r)
{
    if (tree[id].lazy)
    {
        tree[id].min_B += tree[id].lazy;
        tree[id].min_D -= tree[id].lazy;
        tree[id].res = min(tree[id].min_A, tree[id].min_B);

        if (l != r) // not a leaf node
        {
            tree[2 * id].lazy += tree[id].lazy;
            tree[2 * id + 1].lazy += tree[id].lazy;
        }

        tree[id].lazy = 0;
    }
}

void update(int id, int l, int r, int ql, int qr, ll val)
{
    push(id, l, r);
    if (l > qr || r < ql)
        return;             // no overlap
    if (l >= ql && r <= qr) // total overlap
    {
        tree[id].lazy += val;
        push(id, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update(2 * id, l, mid, ql, qr, val);
    update(2 * id + 1, mid + 1, r, ql, qr, val);
    tree[id] = merge(tree[2 * id], tree[2 * id + 1]);
}

void fix(int id, int l, int r, int ql, int qr)
{
    if (l > qr || r < ql)
        return; // no overlap
    push(id, l, r);
    if (tree[id].min_D > 0)
        return;
    if (l == r)
    {
        tree[id].min_B -= INF;
        tree[id].min_A = INF;
        tree[id].lazy = 0;
        tree[id].res = tree[id].min_B;
        tree[id].min_D = INF;
        return;
    }
    int mid = (l + r) / 2;
    fix(2 * id, l, mid, ql, qr);
    fix(2 * id + 1, mid + 1, r, ql, qr);
    tree[id] = merge(tree[2 * id], tree[2 * id + 1]);
}

ll query(int id, int l, int r, int ql, int qr)
{
    push(id, l, r);
    if (l > qr || r < ql)
        return 1e18;
    if (l >= ql && r <= qr)
    {
        return tree[id].res;
    }
    int mid = (l + r) / 2;
    return min(query(2 * id, l, mid, ql, qr), query(2 * id + 1, mid + 1, r, ql, qr));
}

void solve()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }
    build(1, 1, n);
    while (q--)
    {
        ll type, l, r;
        cin >> type >> l >> r;
        if (type == 1)
        {
            ll val;
            cin >> val;
            update(1, 1, n, l, r, val);
            fix(1, 1, n, 1, n);
        }
        else if (type == 2)
        {
            ll ans = query(1, 1, n, l, r);
            cout << ans << '\n';
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