#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int N = 5000 * 30 + 5;

int nodes = 0;
bool isEnd[N];

unordered_map<char, int> trie[N];

void addNode()
{
    isEnd[nodes] = false;
    trie[nodes].clear();
    nodes++;
}

void init()
{
    nodes = 0;
    addNode();
}

void insert(const string &s)
{
    int u = 0;
    for (auto &c : s)
    {
        int &v = trie[u].emplace(c, -1).first->second;
        if (v == -1)
        {
            v = nodes;
            addNode();
        }
        u = v;
    }
    isEnd[u] = true;
}

void print()
{
    for (int u = 0; u < nodes; ++u)
    {
        for (auto &[c, v] : trie[u])
        {
            cout << "FT"[isEnd[u]] << u << ' ' << "FT"[isEnd[v]] << v << ' ' << c << '\n';
        }
    }
}

map<vector<int>, int> ids;

int getId(const vector<int> &v)
{
    return ids.emplace(v, ids.size()).first->second;
}

int dfs(int u)
{
    vector<int> v(27, -1);
    v.back() = isEnd[u];
    for (auto &[c, v2] : trie[u])
    {
        v[c - 'a'] = dfs(v2);
    }
    return getId(v);
}

void solve()
{
    init();
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> s[i];
        insert(s[i]);
    }

    // print();
    dfs(0);
    cout << sz(ids) << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef LOCAL_IO
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
    freopen("language.in", "r", stdin), freopen("language.out", "w", stdout);
#endif

    int tc = 1;
    // cin>>tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}