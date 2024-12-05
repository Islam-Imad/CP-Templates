#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

const int N = 1e6 + 5;
vector<pair<int, int>> prime[N];
int phi[N];

void sieve()
{
    for (int i = 1; i < N; ++i)
        phi[i] = i;
    for (int i = 2; i < N; ++i)
    {
        if (phi[i] == i)
        {
            for (int j = i; j < N; j += i)
            {
                int power = 0, temp = j;
                while (temp % i == 0)
                {
                    temp /= i;
                    power++;
                }
                prime[j].push_back({i, power});
                phi[j] -= phi[j] / i;
                // phi[j] = phi[j] * (i - 1) / i;
            }
        }
    }
}

int sumOfDivisors(int n)
{
    int ans = 1;
    for (auto p : prime[n])
    {
        int pwr = 1;
        for (int i = 0; i < p.Y; ++i)
            pwr *= p.X;
        ans *= (pwr * p.X - 1) / (p.X - 1);
    }
    return ans;
}

int numberOfDivisors(int n)
{
    int ans = 1;
    for (auto p : prime[n])
        ans *= p.Y + 1;
    return ans;
}

int eulerPhi(int n)
{
    int ans = n;
    for (auto p : prime[n])
        ans -= ans / p.X;
    return ans;
}

void solve()
{
    sieve();
    int n;
    cin >> n;
    cout << sumOfDivisors(n) << endl;
    cout << numberOfDivisors(n) << endl;
    cout << eulerPhi(n) << endl;
    cout << phi[n] << endl;
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