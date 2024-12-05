#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

const int N = 1e6 + 5;

vector<int> prime;

void linearSieve()
{
    vector<int> lp(N);
    for (int i = 2; i < N; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            prime.push_back(i);
        }
        for (int j = 0; j < prime.size() && prime[j] <= lp[i] && i * prime[j] < N; ++j)
            lp[i * prime[j]] = prime[j];
    }
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