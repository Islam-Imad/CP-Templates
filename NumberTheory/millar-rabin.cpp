#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second
#define f(c) c - 'a'
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

// From https://github.com/SnapDragon64/ContestLibrary/blob/master/math.h
// which also has specialized versions for 32-bit and 42-bit
//
// Tested:
// - https://oj.vnoi.info/problem/icpc22_national_c (fastest solution)
// - https://www.spoj.com/problems/PON/

// Rabin miller {{{
#define DT __int128_t

inline DT mod_mult64(DT a, DT b, DT m)
{
    return __int128_t(a) * b % m;
}
DT mod_pow64(DT a, DT b, DT m)
{
    DT ret = (m > 1);
    for (;;)
    {
        if (b & 1)
            ret = mod_mult64(ret, a, m);
        if (!(b >>= 1))
            return ret;
        a = mod_mult64(a, a, m);
    }
}

// Works for all primes p < 2^64
bool is_prime(DT n)
{
    if (n <= 3)
        return (n >= 2);
    static const DT small[] = {
        2,
        3,
        5,
        7,
        11,
        13,
        17,
        19,
        23,
        29,
        31,
        37,
        41,
        43,
        47,
        53,
        59,
        61,
        67,
        71,
        73,
        79,
        83,
        89,
        97,
        101,
        103,
        107,
        109,
        113,
        127,
        131,
        137,
        139,
        149,
        151,
        157,
        163,
        167,
        173,
        179,
        181,
        191,
        193,
        197,
        199,
    };
    for (size_t i = 0; i < sizeof(small) / sizeof(DT); ++i)
    {
        if (n % small[i] == 0)
            return n == small[i];
    }

    // Makes use of the known bounds for Miller-Rabin pseudoprimes.
    static const DT millerrabin[] = {
        2,
        3,
        5,
        7,
        11,
        13,
        17,
        19,
        23,
        29,
        31,
        37,
    };
    static const DT A014233[] = {
        // From OEIS.
        204'7LL,
        137'365'3LL,
        253'260'01LL,
        321'503'175'1LL,
        215'230'289'874'7LL,
        347'474'966'038'3LL,
        341'550'071'728'321LL,
        341'550'071'728'321LL,
        382'512'305'654'641'305'1LL,
        382'512'305'654'641'305'1LL,
        382'512'305'654'641'305'1LL,
        0,
    };
    DT s = n - 1, r = 0;
    while (s % 2 == 0)
    {
        s /= 2;
        r++;
    }
    for (size_t i = 0, j; i < sizeof(millerrabin) / sizeof(DT); i++)
    {
        DT md = mod_pow64(millerrabin[i], s, n);
        if (md != 1)
        {
            for (j = 1; j < r; j++)
            {
                if (md == n - 1)
                    break;
                md = mod_mult64(md, md, n);
            }
            if (md != n - 1)
                return false;
        }
        if (n < A014233[i])
            return true;
    }
    return true;
}
// }}}

DT get_num(const string &s)
{
    DT ret = 0;
    for (char c : s)
    {
        if (isdigit(c))
        {
            ret = ret * 10 + (c - '0');
        }
        else
        {
            return -1; // Invalid character
        }
    }
    return ret;
}

DT get_first(DT n)
{
    while (n >= 2)
    {
        if (is_prime(n))
            return n;
        n--;
    }
    return -1;
}

DT get_kth_root(DT n, int k)
{
    long double val = powl(static_cast<long double>(n), 1.0L / k);
    return static_cast<DT>(val);
}

string print(DT num)
{
    string s;
    if (num == 0)
    {
        return "0";
    }
    while (num > 0)
    {
        s.push_back('0' + (num % 10));
        num /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

DT get_prime_factor(DT n)
{
    if (is_prime(n))
        return n;
    for (int k = 2; k; ++k)
    {
        DT root = get_kth_root(n, k);
        DT first = get_first(root);
        if (n % first == 0)
        {
            return first;
        }
    }
    return -1;
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
    cin >> tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}