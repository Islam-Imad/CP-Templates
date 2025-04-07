#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct Kuhn
{
	int n, m;
	vector<vector<int>> adj;
	vector<int> vis;
	vector<int> matchL, matchR;
	Kuhn(int n, int m) : n(n), m(m)
	{
		adj.resize(n);
		vis.resize(n);
		matchL.resize(n, -1);
		matchR.resize(m, -1);
	}
	bool dfs(int u)
	{
		if (vis[u])
			return false;
		vis[u] = true;
		for (int v : adj[u])
		{
			if (matchR[v] == -1 || dfs(matchR[v]))
			{
				matchL[u] = v;
				matchR[v] = u;
				return true;
			}
		}
		return false;
	}
	int maxMatching()
	{
		int ans = 0;
		for (int u = 0; u < n; ++u)
		{
			fill(vis.begin(), vis.end(), 0);
			if (dfs(u))
				ans++;
		}
		return ans;
	}
};

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	Kuhn kuhn(n, m);
	for (int i = 1; i <= k; ++i)
	{
		int u, v;
		cin >> u >> v;
		kuhn.adj[u - 1].push_back(v - 1);
	}
	int ans = kuhn.maxMatching();
	cout << ans << "\n";
	for (int i = 0; i < n; ++i)
	{
		if (kuhn.matchL[i] != -1)
		{
			cout << i + 1 << " " << kuhn.matchL[i] + 1 << "\n";
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