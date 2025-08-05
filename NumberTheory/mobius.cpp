#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int N = 5e5 + 9;

int mob[N];
void mobius()
{
    mob[1] = 1;
    for (int i = 2; i < N; i++)
    {
        mob[i]--;
        for (int j = i + i; j < N; j += i)
        {
            mob[j] -= mob[i];
        }
    }
}

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

/*
# Mobius Function Implementation

```cpp
const int N = 5e5 + 9;

int mob[N];
void mobius()
{
    mob[1] = 1;
    for (int i = 2; i < N; i++)
    {
        mob[i]--;
        for (int j = i + i; j < N; j += i)
        {
            mob[j] -= mob[i];
        }
    }
}
```

## Notes

- F[n] = sigma (d | n) g(d);
- g[d] = sigma (d | n) mob[d] * F[n/d];
- g[d] = sigma (d | n) mob(n/d) * F[d];
- phi[n] = sigma (d | n) mob(d) * (n / d);
- phi[n] / n = sigma (d | n) (mob(d) / d);
*/