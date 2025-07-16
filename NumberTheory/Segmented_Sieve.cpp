#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("Ofast,unroll-loops,fast-math")
#pragma GCC optimize("O3")

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int N = 1e8 + 1;

int cntPrimes = 0;
int prime[5761455];
int lp[N];

void linearSieve()
{
    int i, j;
    for (i = 2; i < N; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            prime[cntPrimes++] = i;
        }
        for (j = 0; i * prime[j] < N; ++j)
        {
            lp[i * prime[j]] = prime[j];
            if (prime[j] == lp[i])
            {
                break;
            }
        }
    }
}

vector<int> segmented_sieve(ll l, ll r)
{
    vector<bool> is_prime(r - l + 1, true);
    if (l == 1)
    {
        is_prime[0] = false; // 1 is not prime
    }
    for (int i = 0; i < cntPrimes; ++i)
    {
        ll cp = prime[i];
        if (cp * cp > r)
            break;
        ll start = max(cp * cp, (l + cp - 1) / cp * cp);
        for (ll j = start; j <= r; j += cp)
        {
            is_prime[j - l] = false;
        }
    }
    vector<int> res;
    for (int i = l; i <= r; ++i)
    {
        if (is_prime[i - l])
            res.push_back(i);
    }
    return res;
}

void solve()
{
    int l, r;
    cin >> l >> r;
    vector<int> primes = segmented_sieve(l, r);
    for(auto &i : primes)
    {
        cout << i << "\n";
    }
    // cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef LOCAL_IO
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    linearSieve();
    auto start = chrono::high_resolution_clock::now();
    int tc = 1;
    cin >> tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << "Time taken: " << time_taken / 1000.0 << " seconds\n";
    return 0;
}