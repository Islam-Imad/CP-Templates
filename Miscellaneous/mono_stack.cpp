#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct monotonic_stack
{
	vector<int> l;
	vector<int> r;
	void work(vector<int> &a)
	{
		int n = a.size();
		l.assign(n, 0);
		r.assign(n, n - 1);
		stack<int> s;
		for (int i = 0; i < n; ++i)
		{
			while (!s.empty() && a[s.top()] >= a[i])
			{
				r[s.top()] = i - 1;
				s.pop();
			}
			s.push(i);
		}
		while (!s.empty())
		{
			s.pop();
		}
		for (int i = n - 1; i >= 0; --i)
		{
			while (!s.empty() && a[s.top()] >= a[i])
			{
				l[s.top()] = i + 1;
				s.pop();
			}
			s.push(i);
		}
		while (!s.empty())
		{
			s.pop();
		}
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