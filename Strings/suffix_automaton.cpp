#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct state
{
	int len;
	int link;
	bool is_clone;
	vector<int> next;
	state() : len(0), link(-1), is_clone(false), next(26, -1) {}
};

struct suffix_automaton
{
	int max_len = 0;
	int position = -1;
	vector<state> st;
	vector<int> first_pos;
	int last;
	suffix_automaton(string const &s)
	{
		st.push_back(state());
		first_pos.push_back(0);
		last = 0;
		for (char c : s)
		{
			st.push_back(state());
			st.back().len = st[last].len + 1;
			first_pos.push_back(st[last].len + 1);
			int cur = st.size() - 1;
			int p = last;
			while (p != -1 && st[p].next[c - 'a'] == -1)
			{
				st[p].next[c - 'a'] = cur;
				p = st[p].link;
			}
			if (p == -1)
			{
				st[cur].link = 0;
			}
			else
			{
				int q = st[p].next[c - 'a'];
				if (st[p].len + 1 == st[q].len)
				{
					if (st[q].len > max_len)
					{
						max_len = st[q].len;
						position = first_pos[q];
					}
					st[cur].link = q;
				}
				else
				{
					st.push_back(state());
					st.back().len = st[p].len + 1;
					st.back().link = st[q].link;
					st.back().is_clone = true;
					st.back().next = st[q].next;
					first_pos.push_back(first_pos[q]);
					int clone = st.size() - 1;
					while (p != -1 && st[p].next[c - 'a'] == q)
					{
						st[p].next[c - 'a'] = clone;
						p = st[p].link;
					}
					if (st[clone].len > max_len)
					{
						max_len = st[clone].len;
						position = first_pos[clone];
					}
					st[q].link = st[cur].link = clone;
				}
			}
			last = cur;
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