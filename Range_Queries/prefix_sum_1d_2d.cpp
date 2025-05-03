#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct prefix_sum_1d
{
	vector<ll> ps;
	prefix_sum_1d(int n) : ps(n + 1) {}
	void add(int i, ll x)
	{
		ps[i] += x;
	}
	void build()
	{
		for (int i = 1; i < ps.size(); ++i)
		{
			ps[i] += ps[i - 1];
		}
	}
	ll qy(ll l)
	{
		return ps[l];
	}
	ll qy(int l, int r)
	{
		return ps[r] - ps[l - 1];
	}
};

struct prefix_sum_2d
{
	vector<vector<ll>> ps;
	prefix_sum_2d(int n, int m) : ps(n + 1, vector<ll>(m + 1)) {}
	void add(int i, int j, ll x)
	{
		ps[i][j] += x;
	}
	void build()
	{
		for (int i = 1; i < ps.size(); ++i)
		{
			for (int j = 1; j < ps[0].size(); ++j)
			{
				ps[i][j] += ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
			}
		}
	}

	ll qy(int x1, int y1)
	{
		return ps[x1][y1];
	}

	ll qy(int x1, int y1, int x2, int y2)
	{
		return ps[x2][y2] - ps[x1 - 1][y2] - ps[x2][y1 - 1] + ps[x1 - 1][y1 - 1];
	}
};

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
	// cin>>tc;
	for (int i = 1; i <= tc; ++i)
	{
		solve();
	}
}