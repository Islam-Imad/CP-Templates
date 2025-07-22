#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct state
{
    int len;
    int link;
    ll cnt = -1;
    map<char, int> next;
    state(int len, int link, map<char, int> next = {})
        : len(len), link(link), next(next) {}
};

struct suffix_automaton
{
    int sz = 0;
    vector<state> st;
    vector<int> occ;
    vector<int> is_cloned;
    int last;
    suffix_automaton(string const &s)
    {
        st.push_back({0, -1});
        is_cloned.push_back(0);
        last = 0;
        for (char c : s)
        {
            st.push_back({st[last].len + 1, 0});
            is_cloned.push_back(0);
            int cur = st.size() - 1;
            int p = last;
            while (p != -1 && !st[p].next.count(c))
            {
                st[p].next[c] = cur;
                p = st[p].link;
            }
            if (p == -1)
            {
                st[cur].link = 0;
            }
            else
            {
                int q = st[p].next[c];
                if (st[p].len + 1 == st[q].len)
                {
                    st[cur].link = q;
                }
                else
                {
                    st.push_back({st[p].len + 1, st[q].link, st[q].next});
                    is_cloned.push_back(1);
                    int clone = (int)(st.size()) - 1;
                    while (p != -1 && st[p].next[c] == q)
                    {
                        st[p].next[c] = clone;
                        p = st[p].link;
                    }
                    st[q].link = st[cur].link = clone;
                }
            }
            last = cur;
        }
        sz = st.size();
    }

    void topological()
    {
        occ.assign(sz, 0);
        vector<int> indeg(sz);
        for (int i = 0; i < sz; ++i)
        {
            if (st[i].link != -1)
            {
                indeg[st[i].link]++;
            }
        }
        queue<int> q;
        for (int i = 0; i < sz; ++i)
        {
            if (indeg[i] == 0)
            {
                q.push(i);
            }
            if (!is_cloned[i])
            {
                occ[i] = 1;
            }
        }
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (st[u].link != -1)
            {
                occ[st[u].link] += occ[u];
                indeg[st[u].link]--;
                if (indeg[st[u].link] == 0)
                {
                    q.push(st[u].link);
                }
            }
        }
    }

    void build_cnt(int u)
    {
        if (st[u].cnt != -1)
            return;
        st[u].cnt = occ[u];
        for (auto &it : st[u].next)
        {
            build_cnt(it.second);
            st[u].cnt += st[it.second].cnt;
        }
    }
};

void solve()
{
    string s;
    cin >> s;
    suffix_automaton sa(s);
    ll kth;
    cin >> kth;
    sa.topological();
    sa.build_cnt(0);
    int v = 0;
    string res = "";
    while (kth > 0)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            if (sa.st[v].next.count(c))
            {
                int next_v = sa.st[v].next[c];
                if (kth > sa.st[next_v].cnt)
                {
                    kth -= sa.st[next_v].cnt;
                }
                else
                {
                    res += c;
                    v = next_v;
                    break;
                }
            }
        }
        kth -= sa.occ[v];
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
}