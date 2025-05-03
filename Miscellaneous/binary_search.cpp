#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct BinarySearch
{

	bool Fx(ll x)
	{
		return false;
	}

	ll search_false_true(ll l, ll r)
	{
		ll ans = -1;
		while (l <= r)
		{
			ll mid = (l + r) >> 1;
			if (Fx(mid))
			{
				ans = mid;
				r = mid - 1;
			}
			else
			{
				l = mid + 1;
			}
		}
		return ans;
	}

	ll search_true_false(ll l, ll r)
	{
		ll ans = -1;
		while (l <= r)
		{
			ll mid = (l + r) >> 1;
			if (Fx(mid))
			{
				l = mid + 1;
			}
			else
			{
				ans = mid;
				r = mid - 1;
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