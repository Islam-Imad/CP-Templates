#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

void radix_sort(vector<pair<pair<int, int>, int>> &arr)
{
    for (int i : vector<int>{2, 1})
    {
        auto key = [&](const pair<pair<int, int>, int> &x)
        {
            return i == 1 ? x.first.first : x.first.second;
        };
        int max = 0;
        for (const auto &i : arr)
        {
            max = std::max(max, key(i));
        }
        vector<int> occs(max + 1);
        for (const auto &i : arr)
        {
            occs[key(i)]++;
        }
        vector<int> start(max + 1);
        for (int i = 1; i <= max; i++)
        {
            start[i] = start[i - 1] + occs[i - 1];
        }

        vector<pair<pair<int, int>, int>> new_arr(arr.size());
        for (const auto &i : arr)
        {
            new_arr[start[key(i)]] = i;
            start[key(i)]++;
        }
        arr = new_arr;
    }
}

struct SuffixArray
{

    int n;
    string s;
    vector<int> suffixesIdx;
    vector<pair<pair<int, int>, int>> suffixes;
    vector<int> sortingOrder;
    vector<int> lcp;

    void Set_String(const string &str)
    {
        s = str + ' '; // or s += '$' but be aware
        n = s.size();
        suffixes.resize(n);
        sortingOrder.resize(n);
        suffixesIdx.resize(n);
        lcp.resize(n - 1);
    }

    void Sort()
    {
        for (int i = 1; i < n; ++i)
        {
            pair<int, int> c_val = suffixes[i].X;
            pair<int, int> p_val = suffixes[i - 1].X;
            sortingOrder[suffixes[i].Y] = sortingOrder[suffixes[i - 1].Y] + (c_val > p_val);
        }
    }

    void Build()
    {
        for (int i = 0; i < n; ++i)
        {
            suffixes[i] = {{s[i], s[i]}, i};
        }
        sort(suffixes.begin(), suffixes.end());
        Sort();
        for (int len = 1; len < n; len *= 2)
        {
            for (auto &[val, idx] : suffixes)
            {
                val = {sortingOrder[idx], sortingOrder[(idx + len) % n]};
            }

            radix_sort(suffixes);
            // sort(suffixes.begin(), suffixes.end()); // if you want to use std::sort instead of radix_sort
            Sort();
        }
        for (int i = 0; i < n; ++i)
        {
            suffixesIdx[suffixes[i].Y] = i;
        }
        int start_at = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int prev_idx = suffixes[suffixesIdx[i] - 1].Y;
            while (s[i + start_at] == s[prev_idx + start_at])
            {
                start_at++;
            }
            lcp[suffixesIdx[i] - 1] = start_at;
            start_at = max(start_at - 1, 0);
        }
    }

    void print_lcp()
    {
        for (int i = 0; i < n - 1; ++i)
        {
            cout << lcp[i] << " ";
        }
        cout << '\n';
    }

    void print_suffixes()
    {
        for (int i = 0; i < n; ++i)
        {
            cout << suffixes[i].Y << " " << s.substr(suffixes[i].Y) << '\n';
        }
    }

    void Query()
    {
        for (int i = 1; i < n; ++i)
        {
            cout << suffixes[i].Y << " ";
        }
        cout << '\n';
    }

    void Query(ll kth)
    {
        vector<int> vis(n, 0);
        for (int i = 0; i < n - 1; ++i)
        {
            int idx = vis[i];
            while (kth > 0 and idx < (n - 1 - suffixes[i + 1].Y))
            {
                idx += 1;
                kth -= 1;
                for (int j = i + 1; j < n - 1 and kth > 0; ++j)
                {
                    if (lcp[j] >= idx)
                    {
                        kth -= 1;
                        vis[j] = idx;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if (kth == 0)
            {
                cout << s.substr(suffixes[i + 1].Y, idx) << '\n';
                return;
            }
        }
    }
};

void solve()
{
    SuffixArray sa;
    string s;
    cin >> s;
    sa.Set_String(s);
    sa.Build();
    sa.Query();
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
    // #endif
    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}