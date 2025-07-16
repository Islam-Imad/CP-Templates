#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

struct Node
{
    int freq;
    Node *left;
    Node *right;
    Node() : freq(0), left(nullptr), right(nullptr) {}
    Node(int f) : freq(f), left(nullptr), right(nullptr) {}
    Node(int f, Node *l, Node *r) : freq(f), left(l), right(r) {}
    ~Node()
    {
        if (left)
            delete left;
        if (right)
            delete right;
        left = right = nullptr;
        freq = 0;
    }
};

struct BinaryTrie
{
    Node *root;
    BinaryTrie() : root(new Node()) {}
    ~BinaryTrie() { delete root; }
    
    void Insert(ll num)
    {
        Node *curr = root;  // ✅ Use separate pointer
        for (ll bit = 63; bit >= 0; --bit)
        {
            int b = (num >> bit) & 1;
            if (b == 0)
            {
                if (!curr->left)
                    curr->left = new Node();
                curr = curr->left;
            }
            else
            {
                if (!curr->right)
                    curr->right = new Node();
                curr = curr->right;
            }
            curr->freq++;
        }
    }

    void Remove(ll num)
    {
        Node *curr = root;  // ✅ Use separate pointer
        for (ll bit = 63; bit >= 0; --bit)
        {
            int b = (num >> bit) & 1;
            if (b == 0)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
            if (curr) curr->freq--;  // ✅ Add null check
        }
    }

    ll maxXor(ll num)
    {
        Node *node = root;
        ll ans = 0;
        for (ll bit = 63; bit >= 0; --bit)
        {
            int b = (num >> bit) & 1;
            if (b == 0)
            {
                if (node->right && node->right->freq > 0)
                {
                    ans |= (1LL << bit);
                    node = node->right;
                }
                else
                {
                    node = node->left;
                }
            }
            else
            {
                if (node->left && node->left->freq > 0)
                {
                    ans |= (1LL << bit);
                    node = node->left;
                }
                else
                {
                    node = node->right;
                }
            }
        }
        return ans;
    }

    ll minXor(ll num)
    {
        Node *node = root;
        ll ans = 0;
        for (ll bit = 63; bit >= 0; --bit)
        {
            int b = (num >> bit) & 1;
            if (b == 0)
            {
                if (node->left && node->left->freq > 0)
                {
                    node = node->left;
                }
                else
                {
                    ans |= (1LL << bit);
                    node = node->right;
                }
            }
            else
            {
                if (node->right && node->right->freq > 0)
                {
                    node = node->right;
                }
                else
                {
                    ans |= (1LL << bit);
                    node = node->left;
                }
            }
        }
        return ans;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<ll> arr(n);
    BinaryTrie trie;
    ll xr = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    ll res = 0;
    trie.Insert(0);
    
    // Uncommented working version
    for (int i = 0; i < n; ++i)
    {
        xr ^= arr[i];
        res = max(res, trie.maxXor(xr));
        trie.Insert(xr);
    }
    cout << res << '\n';
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
    return 0;
}