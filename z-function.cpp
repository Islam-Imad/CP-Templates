#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

vector<int> z_function(const string &s)
{
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++)
    {
        z[i] = max(0, min(z[i - l], r - i + 1));

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            l = i;
            r = i + z[i];
            z[i]++;
        }
    }
    return z;
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