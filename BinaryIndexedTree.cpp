/*
    Prefix Query with point update
    e.g(sum , max)
    Default: sum
    Editorial: https://usaco.guide/CPH.pdf#page=96
    Time Complexity: O(logN)
    Space Complexity: O(N)
    1-based indexing
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

template <class T>
struct BIT
{
    int size;
    vector<T> bit;
    BIT(int size) 
    : size(size)
    , bit(size + 1) 
    {
        
    }

    void update(int idx, T val)
    {
        for (; idx <= size; idx += (idx & -idx))
        {
            bit[idx] += val;
        }
    }

    T Query(int idx)
    {
        T total{};
        for (; idx > 0; idx -= idx & -idx)
        {
            total += bit[idx];
        }
        return total;
    }

    T Query(int l, int r)
    {
        assert(l <= r);
        return Query(r) - Query(l - 1);
    }
};

void solve(){
    
}

int main()
{
ios_base::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
    int tc = 1;
    // cin>>tc;
    for(int i=1;i<=tc;++i){
        solve();
    }
}