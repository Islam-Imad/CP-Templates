#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

class HashedString
{
private:
    static const long long POW;
    static const long long MOD = (1LL << 61) - 1;
    static const int MANX = 1e6 + 5;
    static vector<long long> get_pow;
    vector<long long> get_hash;

    static __int128_t mul(long long a, long long b)
    {
        return (__int128_t)a * b;
    }

    static long long mod_mul(long long a, long long b)
    {
        return mul(a, b) % MOD;
    }

    static void calcPow()
    {
        if (!get_pow.empty()) // already calculated
            return;
        get_pow.assign(MANX, 1);
        for (int i = 1; i < MANX; i++)
            get_pow[i] = mod_mul(get_pow[i - 1], POW);
    }

    void calcHash(const string &str)
    {
        get_hash.assign(str.size() + 2, 0);
        for (int i = 0; i < str.size(); i++)
            get_hash[i + 1] = (mod_mul(get_hash[i], POW) + str[i]) % MOD;
    }

public:
    HashedString(const string &str)
        : get_hash(str.size() + 2, 0)
    {
        calcPow();
        calcHash(str);
    }

    long long getHash(int l, int r) const
    {   // l and r are zero based
        return (((get_hash[r + 1] - mod_mul(get_hash[l], get_pow[r - l + 1]) + MOD) % MOD) + MOD) % MOD;
    }
};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
const long long HashedString::POW = uniform_int_distribution<long long>(31, 31)(rng);
vector<long long> HashedString::get_pow = {};

void solve(){
    HashedString hs("a");
    cout << hs.getHash(0, 0) << endl;
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