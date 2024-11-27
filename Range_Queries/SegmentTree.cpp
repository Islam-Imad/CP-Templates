#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

// handle base zero and one
template <typename T, typename U>
class SegmentTree
{
private:

    #define lc(node) (2 * node)
    #define rc(node) (2 * node + 1)
    #define mid(left, right) ((left + right) / 2)
    
    const T DEFAULT = 0; // Replace this line with DEFAULT
    const U NO_UPDATE = 0; // Replace this line with NO_UPDATE
    int size;
    vector<T> seg_tree;
    vector<U> lazy;

    T Operation(T a, T b){
        T res = min(a,b); // edit this line
        return res;
    }

    void Propogate(int node, int l, int r){
        // edit this also
        if (lazy[node] != NO_UPDATE){
            seg_tree[node] += lazy[node];
            if (l != r)
            {
                lazy[lc(node)] = lazy[node];
                lazy[rc(node)] = lazy[node];
            }
            lazy[node] = NO_UPDATE;
        }
    }

    void Build(int node, int l, int r, const vector<T> &arr){
        if (l == r){
            seg_tree[node] = arr[l]; // edit this line (base zero or base one)
            return;
        }
        Build(lc(node), l, mid(l, r), arr);
        Build(rc(node), mid(l, r) + 1, r, arr);
        seg_tree[node] = Operation(seg_tree[lc(node)], seg_tree[rc(node)]);
    }

    void Update(int node, int l, int r, int ul, int ur, U val){
        Propogate(node, l, r);
        if (l > ur || r < ul)
            return;
        if (l >= ul && r <= ur){
            lazy[node] += val;
            Propogate(node, l, r);
            return;
        }
        Update(lc(node), l, mid(l, r), ul, ur, val);
        Update(rc(node), mid(l, r) + 1, r, ul, ur, val);
        seg_tree[node] = Operation(seg_tree[lc(node)], seg_tree[rc(node)]);
    }

    U Query(int node, int l, int r, int ql, int qr){
        Propogate(node, l, r);
        if (l > qr || r < ql)
            return DEFAULT;
        if (l >= ql && r <= qr)
            return seg_tree[node]; // Return the data member of the node struct
        return Operation(Query(lc(node), l, mid(l, r), ql, qr), Query(rc(node), mid(l, r) + 1, r, ql, qr));
    }

public:
    SegmentTree() = default;
    SegmentTree(U DEFAULT,U NO_UPDATE, int size, const vector<T> &arr = {}) // Replace DEFAULT with T DEFAULT
    : size(size)
    , DEFAULT(DEFAULT)
    , NO_UPDATE(NO_UPDATE)
    , lazy(4 * (size + 1),NO_UPDATE)
    , seg_tree(4 * (size + 1),DEFAULT)
    {
        if (!arr.empty())
            Build(1, 1, size, arr);
    };

    void Update(int l, int r, U val)
    {
        Update(1, 1, size, l, r, val);
    }

    U Query(int l, int r){
        return Query(1, 1, size, l, r);
    }
};

void solve(){
    SegmentTree<ll,ll> st(0,0,10);
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
