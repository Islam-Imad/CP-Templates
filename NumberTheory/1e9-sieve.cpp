#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")

#define ll long long int
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
vector<int> sieve(const int N, const int Q = 17, const int L = 1 << 15)
{
    static const int rs[] = {1, 7, 11, 13, 17, 19, 23, 29};
    struct P
    {
        P(int p) : p(p) {}
        int p;
        int pos[8];
    };
    auto approx_prime_count = [](const int N) -> int
    {
        return N > 60184 ? N / (log(N) - 1.1)
                         : max(1., N / (log(N) - 1.11)) + 1;
    };

    const int v = sqrt(N), vv = sqrt(v);
    vector<bool> isp(v + 1, true);
    for (int i = 2; i <= vv; ++i)
        if (isp[i])
        {
            for (int j = i * i; j <= v; j += i)
                isp[j] = false;
        }

    const int rsize = approx_prime_count(N + 30);
    vector<int> primes = {2, 3, 5};
    int psize = 3;
    primes.resize(rsize);

    vector<P> sprimes;
    size_t pbeg = 0;
    int prod = 1;
    for (int p = 7; p <= v; ++p)
    {
        if (!isp[p])
            continue;
        if (p <= Q)
            prod *= p, ++pbeg, primes[psize++] = p;
        auto pp = P(p);
        for (int t = 0; t < 8; ++t)
        {
            int j = (p <= Q) ? p : p * p;
            while (j % 30 != rs[t])
                j += p << 1;
            pp.pos[t] = j / 30;
        }
        sprimes.push_back(pp);
    }

    vector<unsigned char> pre(prod, 0xFF);
    for (size_t pi = 0; pi < pbeg; ++pi)
    {
        auto pp = sprimes[pi];
        const int p = pp.p;
        for (int t = 0; t < 8; ++t)
        {
            const unsigned char m = ~(1 << t);
            for (int i = pp.pos[t]; i < prod; i += p)
                pre[i] &= m;
        }
    }

    const int block_size = (L + prod - 1) / prod * prod;
    vector<unsigned char> block(block_size);
    unsigned char *pblock = block.data();
    const int M = (N + 29) / 30;

    for (int beg = 0; beg < M; beg += block_size, pblock -= block_size)
    {
        int end = min(M, beg + block_size);
        for (int i = beg; i < end; i += prod)
        {
            copy(pre.begin(), pre.end(), pblock + i);
        }
        if (beg == 0)
            pblock[0] &= 0xFE;
        for (size_t pi = pbeg; pi < sprimes.size(); ++pi)
        {
            auto &pp = sprimes[pi];
            const int p = pp.p;
            for (int t = 0; t < 8; ++t)
            {
                int i = pp.pos[t];
                const unsigned char m = ~(1 << t);
                for (; i < end; i += p)
                    pblock[i] &= m;
                pp.pos[t] = i;
            }
        }
        for (int i = beg; i < end; ++i)
        {
            for (int m = pblock[i]; m > 0; m &= m - 1)
            {
                primes[psize++] = i * 30 + rs[__builtin_ctz(m)];
            }
        }
    }
    assert(psize <= rsize);
    while (psize > 0 && primes[psize - 1] > N)
        --psize;
    primes.resize(psize);
    return primes;
}

void solve()
{
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> primes = sieve(n);
    int m = primes.size();
    vector<int> res;
    for (int i = b; i < m; i += a)
    {
        res.push_back(primes[i]);
    }
    cout << m << ' ' << res.size() << '\n';
    for (auto &i : res)
    {
        cout << i << ' ';
    }
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
        start_timer();
        solve();
        double elapsed = get_elapsed_time();
        cerr << "Test case " << i << " completed in " << fixed << setprecision(3) << elapsed << " ms\n";
    }
}