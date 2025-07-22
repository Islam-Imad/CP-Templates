#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct SCC
{
    int n, cnt, dfs_num;
    vector<vector<int>> adj, dagList;
    vector<int> inStack, lowLink, dfn, comp;
    stack<int> st;
    vector<vector<int>> scc;
    vector<int> artipoints;

    vector<pair<int, int>> ciriticalEdges;

    stack<pair<int, int>> bi_comps;

    bool root = false;

    SCC(int n)
        : n(n), cnt(0), adj(n), inStack(n), lowLink(n), dfn(n, -1), comp(n, -1), dfs_num(0)
    {
        artipoints.assign(n, 0);
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void dfs(int node)
    {
        inStack[node] = 1;
        for (auto &child : dagList[node])
        {
            if (!inStack[child])
            {
                dfs(child);
            }
        }
    }

    void tarjan(int node, int parent = -1)
    {
        lowLink[node] = dfn[node] = dfs_num++, inStack[node] = 1;
        st.push(node);
        int to_parent = 0;
        for (auto &child : adj[node])
        {
            if (child == parent and to_parent == 0)
            {
                to_parent = 1;
                continue;
            }
            if (dfn[child] == -1)
            {
                tarjan(child, node);
                lowLink[node] = min(lowLink[node], lowLink[child]);
                if ((lowLink[child] >= dfn[node]) and (dfn[node] or root))
                {
                    artipoints[node] = 1;
                }
                if (dfn[node] == 0 and root == false)
                {
                    root = true;
                }
            }
            else if (inStack[child])
            {
                lowLink[node] = min(lowLink[node], dfn[child]);
            }
        }
        if (lowLink[node] == dfn[node])
        {
            if (parent != -1)
            {
                ciriticalEdges.push_back({parent, node});
            }
            scc.push_back({});
            while (true)
            {
                int v = st.top();
                st.pop();
                inStack[v] = 0;
                scc.back().push_back(v);
                comp[v] = cnt;
                if (v == node)
                    break;
            }
            cnt++;
        }
    }

    void get_dag_list()
    {
        dagList.resize(cnt);
        for (int i = 0; i < n; i++)
        {
            for (auto &child : adj[i])
            {
                if (comp[i] != comp[child])
                {
                    dagList[comp[i]].push_back(comp[child]);
                }
            }
        }
    }

    void run()
    {
        for (int i = 0; i < n; i++)
        {
            if (dfn[i] == -1)
            {
                tarjan(i);
            }
        }
    }
};

/*
@Problems:
https://www.spoj.com/problems/EC_P/
https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_B
https://judge.yosupo.jp/problem/two_edge_connected_components
https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_A
*/

void solve()
{
    int n, m;
    cin >> n >> m;
    SCC scc(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        scc.add_edge(u, v);
        scc.add_edge(v, u);
    }
    scc.run();
    cout << scc.cnt << '\n';
    for (int i = 0; i < scc.cnt; i++)
    {
        cout << scc.scc[i].size() << ' ';
        for (auto &v : scc.scc[i])
        {
            cout << v << ' ';
        }
        cout << '\n';
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