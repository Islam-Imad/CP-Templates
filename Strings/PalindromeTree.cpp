#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define size(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int N = 1e5 + 5;
#define arr(t, n, mn, mx) t n##_[(mx) - (mn) + 1], *n = (n##_) - (mn)
typedef map<char, int> mci;

arr(int, pos, -1, N);
arr(int, len, -1, N);
arr(int, fail, -1, N);
arr(int, nd, -1, N);
arr(int, curSz, -1, N);
arr(int, par, -1, N);
arr(char, str, -1, N);
arr(mci, child, -1, N);
int lst, sz;

int addNode(int l, int p)
{
    pos[sz] = p;
    len[sz] = l;
    child[sz].clear();
    return sz++;
}

void init()
{
    str[-1] = -1;
    sz = lst = -1;
    addNode(-1, -1);
    addNode(0, 0);
    fail[0] = -1;
}

int getFail(int cur, int idx)
{
    auto c = str[idx];
    while (1)
    {
        int m = idx - len[cur] - 1;
        if (c == str[m])
            break;
        cur = fail[cur];
    }
    return cur;
}

int addChar(int idx)
{
    auto cur = getFail(lst, idx);
    auto c = str[idx];
    auto &nxt = child[cur].emplace(c, -1).first->second;
    if (~nxt)
    {
        lst = nxt;
        nd[idx] = nxt;
        curSz[idx] = sz;
        return 0;
    }
    lst = nxt = addNode(len[cur] + 2, idx);
    nd[idx] = nxt;
    par[nxt] = cur;
    curSz[idx] = sz;
    int f = 0;
    if (~cur)
    {
        cur = getFail(fail[cur], idx);
        f = child[cur][c];
    }
    fail[nxt] = f;
    return 1;
}

void bld()
{
    init();
    for (int i = 0; str[i]; ++i)
    {
        addChar(i);
    }
}

void print()
{
    for (int u = -1; u < sz; ++u)
    {
        for (auto [c, v] : child[u])
            printf("%d,%d,%d,%d %d,%d,%d,%d %c\n", u, len[u], pos[u], fail[u], v, len[v], pos[v], fail[v], c);
    }
}

void longest_palindrome()
{
    int index = -1;
    int length = -1;
    for (int u = -1; u < sz; ++u)
    {
        for (auto [c, v] : child[u])
        {
            if (len[v] > length)
            {
                length = len[v];
                index = pos[v];
            }
        }
    }
    index = index - length + 1;
    for (int i = index; i < index + length; ++i)
    {
        cout << str[i];
    }
    cout << '\n';
}

void solve()
{
    string s;
    cin >> s;
    for (int i = 0; i < size(s); ++i)
        str[i] = s[i];
    str[size(s)] = 0;
    bld();
    for (int i = 0; i < size(s); ++i)
    {
        cout << curSz[i] - 1 << ' ';
    }
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef LOCAL_IO
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}