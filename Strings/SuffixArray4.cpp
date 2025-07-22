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
    vector<int> belong;
    int tot = 0;
    void add_string(const string &str)
    {
        if (tot == 0)
        {
            s = str;
        }
        else
        {
            belong.push_back(tot);
            s += "|" + str;
        }
        tot += 1;
        for (auto &c : str)
        {
            belong.push_back(tot);
        }
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
        belong.push_back(0);
        s += ' ';
        n = s.size();
        suffixes.resize(n);
        sortingOrder.resize(n);
        suffixesIdx.resize(n);
        lcp.resize(n - 1);
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
            while (s[i + start_at] == s[prev_idx + start_at] and s[i + start_at] != '|')
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
            cout << belong[suffixes[i].Y] << ' ' << suffixes[i].Y << " " << s.substr(suffixes[i].Y) << '\n';
        }
    }

    void Query()
    {
        map<int, int> vis;
        int cnt = 0;
        int last = 0;
        int lim = 1 + (tot) / 2;
        int res = 0;
        multiset<int> sts;
        vector<int> strs;
        for (int i = 0; i < n - 1; ++i)
        {
            int idx = suffixes[i + 1].Y;
            if (s[idx] == '|')
            {
                cnt = 0;
                last = i + 1;
                sts.clear();
                vis.clear();
                continue;
            }
            idx = belong[idx];
            if (vis.count(idx) == 0)
            {
                cnt += 1;
            }
            vis[idx] += 1;
            sts.insert(lcp[i]);
            while (cnt > lim)
            {
                auto it = sts.find(lcp[last]);
                sts.erase(it);
                int prev_idx = suffixes[last + 1].Y;
                last += 1;
                prev_idx = belong[prev_idx];
                vis[prev_idx] -= 1;
                if (vis[prev_idx] == 0)
                {
                    vis.erase(prev_idx);
                    cnt -= 1;
                }
            }
            while (cnt == lim)
            {
                auto it = sts.find(lcp[last]);
                int prev_idx = suffixes[last + 1].Y;
                prev_idx = belong[prev_idx];
                assert(prev_idx > 0);
                if (vis[prev_idx] == 1)
                {
                    break;
                }
                else
                {
                    sts.erase(it);
                    vis[prev_idx] -= 1;
                    last += 1;
                }
            }
            if (cnt >= lim)
            {
                auto it = sts.begin();
                if (*it == lcp[last])
                {
                    it++;
                }
                if (*it > res)
                {
                    res = *it;
                    strs.clear();
                    strs.push_back(suffixes[i + 1].Y);
                }
                else if (*it == res)
                {
                    strs.push_back(suffixes[i + 1].Y);
                }
            }
        }
        // cout << res << '\n';
        if (res == 0)
        {
            cout << "?\n";
        }
        else
        {
            set<string> unistrs;
            for (const auto &idx : strs)
            {
                string cur = s.substr(idx, res);
                if (unistrs.count(cur) == 0)
                {
                    cout << cur << '\n';
                    unistrs.insert(cur);
                }
            }
        }
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
    int n;
    bool fi = false;
    while (cin >> n and n)
    {
        if (fi)
        {
            cout << '\n';
        }
        fi = true;
        if (n == 1)
        {
            string s;
            cin >> s;
            cout << s << '\n';
            continue;
        }
        SuffixArray sa;
        for (int j = 0; j < n; ++j)
        {
            string str;
            cin >> str;
            sa.add_string(str);
        }
        sa.Build();
        sa.Query();
    }
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifdef LOCAL_IO
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; ++i)
    {
        solve();
    }
}