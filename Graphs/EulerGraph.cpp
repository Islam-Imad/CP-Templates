#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct EulerGraph
{
	int nodes;
	int edges;
	vector<set<int>> adj;
	vector<int> degree;
	vector<int> visited;
	EulerGraph(int n, int m) : nodes(n), edges(m), adj(n), degree(n, 0), visited(m, 0) {}
	void addEdge(int u, int v)
	{
		adj[u].insert(v);
		adj[v].insert(u);
		degree[u]++;
		degree[v]++;
	}

	vector<int> eulerianPath()
	{
		int oddCount = 0;
		int startNode = -1;
		for (int i = 0; i < nodes; ++i)
		{
			if (degree[i] % 2 == 1)
			{
				oddCount++;
				startNode = i;
			}
		}

		if (oddCount != 0 and oddCount != 2)
			return {};

		if (startNode == -1) // All vertices have even degree, start from any vertex
			startNode = 0;

		vector<int> path;
		stack<int> stack;
		stack.push(startNode);

		while (!stack.empty())
		{
			int u = stack.top();
			if (adj[u].empty())
			{
				path.push_back(u);
				stack.pop();
			}
			else
			{
				int v = *adj[u].begin();
				stack.push(v);
				adj[u].erase(v);
				adj[v].erase(u);
			}
		}

		reverse(path.begin(), path.end());
		return path;
	}
};

struct ID
{
	const int OFFSET = 0;
	ID(int n) : OFFSET(n) {}
	map<int, int> idMap;
	int get(int x)
	{
		if (idMap.find(x) == idMap.end())
		{
			int newId = idMap.size() + OFFSET;
			idMap[x] = newId;
			return newId;
		}
		return idMap[x];
	}
};

void solve()
{
	int n;
	cin >> n;
	ID a(0), b(0);
	vector<pair<int, int>> edges;
	map<pair<int, int>, int> Idx;
	for (int i = 0; i < n; ++i)
	{
		int x, y;
		cin >> x >> y;
		x = a.get(x);
		y = b.get(y);
		edges.emplace_back(x, y);
	}
	int offset = a.idMap.size();
	int sz = a.idMap.size() + b.idMap.size();
	for (int i = 0; i < n; ++i)
	{
		pair<int, int> &p = edges[i];
		p.second += offset;
		Idx[p] = i;
		// cout << p.first + 1 << " " << p.second + 1 << "\n"; // Convert to 1-based index
	}
	EulerGraph graph(sz, n);
	for (auto &p : edges)
	{
		graph.addEdge(p.first, p.second);
	}
	vector<int> path = graph.eulerianPath();
	if (path.size() != n + 1)
	{
		cout << "NO\n";
		return;
	}
	vector<int> ans(n);
	for (int i = 0; i < n; ++i)
	{
		pair<int, int> p = {path[i], path[i + 1]};
		if (p.first > p.second)
			swap(p.first, p.second);
		if (Idx.find(p) == Idx.end())
		{
			cout << "NO\n";
			return;
		}
		ans[i] = Idx[p];
	}
	cout << "YES\n";
	for (int i = 0; i < n; ++i)
	{
		cout << ans[i] + 1 << " "; // Convert to 1-based index
	}
	cout << "\n";
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