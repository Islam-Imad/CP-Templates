#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

void solve()
{
    int n;
    string s;
    cin >> s, s += '$', n = s.size();
    vector<pair<pair<int, int>, int>> suffixes(n);
    vector<int> lcp(n - 1), sortingOrder(n), suffixesIdx(n);
    for (int i = 0; i < n; ++i)
    {
        suffixes[i] = {{s[i], s[i]}, i};
    }
    sort(suffixes.begin(), suffixes.end());
    for (int i = 1; i < n; ++i)
    {
        auto c_val = suffixes[i].X;
        auto p_val = suffixes[i - 1].X;
        sortingOrder[suffixes[i].Y] = sortingOrder[suffixes[i - 1].Y] + (c_val > p_val);
    }
    for (int len = 1; len < n; len *= 2)
    {
        for (auto &[val, idx] : suffixes)
        {
            val = {sortingOrder[idx], sortingOrder[(idx + len) % n]};
        }

        sort(suffixes.begin(), suffixes.end());

        for (int i = 1; i < n; ++i)
        {
            auto c_val = suffixes[i].X;
            auto p_val = suffixes[i - 1].X;
            sortingOrder[suffixes[i].Y] = sortingOrder[suffixes[i - 1].Y] + (c_val > p_val);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        suffixesIdx[suffixes[i].Y] = i;
    }
    int start_at = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int prev_idx = suffixes[suffixesIdx[i] - 1].Y;
        while (s[i + start_at] == s[prev_idx + start_at])
        {
            start_at++;
        }
        lcp[suffixesIdx[i] - 1] = start_at;
        start_at = max(start_at - 1, 0);
    }
    for (int i = 0; i < n - 1; ++i)
    {
        cout << lcp[i] << " \n"[i == n - 2];
    }
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin>>tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}