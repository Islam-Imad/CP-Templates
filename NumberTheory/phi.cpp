
#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")

#define int long long
#define ll long long
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

auto start_time = chrono::high_resolution_clock::now();

void start_timer()
{
    start_time = chrono::high_resolution_clock::now();
}

double get_elapsed_time()
{
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    return duration.count() / 1000.0; // Return in milliseconds
}

ll phi(ll num)
{
    ll res = num;
    for (ll d = 2; d * d <= num; d++)
    {
        if (num % d == 0)
        {
            while (num % d == 0)
                num /= d;
            res -= res / d;
        }
    }
    if (num > 1)
        res -= res / num;
    return res;
}
/*
https://www.spoj.com/problems/ETF/
*/
/*
    phi[i] = the number of integers from 1 to i that are coprime with i
    phi(a * b) = phi(a) * phi(b) when a and b are coprime or __gcd(a,b) == 1
    phi(p ^ k) = p ^ k - p ^ (k - 1) = p ^ (k - 1) * (p - 1) where p is prime and k >= 1
*/
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

vector<int> phi(ll l, ll r)
{
    vector<int> res(r - l + 1);
    vector<int> rem(r - l + 1);
    for (int i = l; i <= r; ++i)
    {
        res[i - l] = i;
        rem[i - l] = i;
    }
    for (int i = 0; i < cntPrimes; ++i)
    {
        ll cp = prime[i];
        if (cp * cp > r)
            break;
        ll start = max(cp * cp, (l + cp - 1) / cp * cp);
        for (ll j = start; j <= r; j += cp)
        {
            int idx = j - l;
            if (rem[idx] % cp == 0)
            {
                while (rem[idx] % cp == 0)
                {
                    rem[idx] /= cp;
                }
                res[idx] -= res[idx] / cp;
            }
        }
    }
    for (int i = 0; i < r - l + 1; ++i)
    {
        if (rem[i] > 1)
        {
            res[i] -= res[i] / rem[i];
        }
    }
    return res;
}

void solve()
{
    linearSieve();
    int l, r;
    cin >> l >> r;
    vector<int> result = phi(l, r);
    for (int i = 0; i < result.size(); ++i)
    {
        cout << result[i] << '\n';
    }
}


signed main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef LOCAL_IO
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; ++i)
    {
        start_timer();
        solve();
        double elapsed = get_elapsed_time();
        cerr << "Test case " << i << " completed in " << fixed << setprecision(3) << elapsed << " ms\n";
    }
}