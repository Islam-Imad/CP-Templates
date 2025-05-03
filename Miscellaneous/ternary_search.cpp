#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct Ternary_Search
{
	ll Fx(ll x)
	{
		return -1;
	}

	ll search_min(ll l, ll r)
	{
		ll ans = -1;
		while (l <= r)
		{
			ll m1 = l + (r - l) / 3;
			ll m2 = r - (r - l) / 3;
			if (Fx(m1) < Fx(m2))
			{
				ans = m1;
				r = m2 - 1;
			}
			else
			{
				ans = m2;
				l = m1 + 1;
			}
		}
		return ans;
	}

	ll search_max(ll l, ll r)
	{
		ll ans = -1;
		while (l <= r)
		{
			ll m1 = l + (r - l) / 3;
			ll m2 = r - (r - l) / 3;
			if (Fx(m1) > Fx(m2))
			{
				ans = m1;
				r = m2 - 1;
			}
			else
			{
				ans = m2;
				l = m1 + 1;
			}
		}
		return ans;
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