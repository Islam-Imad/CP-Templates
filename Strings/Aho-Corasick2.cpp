#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int K = 26;

struct Vertex
{
    int next[K];
    int go[K];

    int output = 0;
    int total = -1;

    int p = -1;
    char pch;
    int link = -1;

    Vertex(int p = -1, char ch = '$')
        : p(p), pch(ch)
    {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

struct AhoCorasick
{
    vector<Vertex> t;
    AhoCorasick()
    {
        t = vector<Vertex>(1);
    }
    int add_string(string const &s, int val)
    {
        int v = 0;
        for (char ch : s)
        {
            int c = f(ch);
            if (t[v].next[c] == -1)
            {
                t[v].next[c] = t.size();
                t.emplace_back(v, ch);
            }
            v = t[v].next[c];
        }
        t[v].output += val;
        return v;
    }

    int get_link(int v)
    {
        if (t[v].link == -1)
        {
            if (v == 0 || t[v].p == 0)
                t[v].link = 0;
            else
                t[v].link = go(get_link(t[v].p), t[v].pch);
        }
        return t[v].link;
    }

    int go(int v, char ch)
    {
        int c = f(ch);
        if (t[v].go[c] == -1)
        {
            if (t[v].next[c] != -1)
                t[v].go[c] = t[v].next[c];
            else
                t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return t[v].go[c];
    }
    int getTotal(int v)
    {
        if (v == 0)
            return 0;
        if (t[v].total == -1)
        {
            t[v].total = t[v].output + getTotal(get_link(v));
        }
        return t[v].total;
    }
};

/*
the string may be added more than one :) 
*/

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