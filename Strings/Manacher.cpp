#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

vector<int> manacher_odd(string s)
{
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]])
        {
            p[i]++;
        }
        if (i + p[i] > r)
        {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<pair<int, int>> manacher(string s)
{
    int n = s.size();
    string t = "";
    for (auto c : s)
        t += "|", t += c;
    t += "|";
    vector<int> p = manacher_odd(t);
    vector<pair<int, int>> res(n);
    for (int i = 0; i < n; ++i)
    {
        res[i] = {p[i + i + 1] / 2, p[i + i + 2] / 2};
        // First ( . . . i . . .) l = i - (First - 1) , r = i + (First - 1)
        // Second (. . i i+1 . . ) l = i - (Second - 1), r = i + 1 + (Second - 1)
        // if second is zero l > r
    }
    return res;
}

void solve()
{
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