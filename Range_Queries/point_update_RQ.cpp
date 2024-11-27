/*
    Range Query with point update
    (min , max , sum , gcd , ..)
    Time Complexity : O(log(n))
    Space Complexity : O(n)
    1 based indexing

    =>> allow you to update a single element and query on a range
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

template <typename T>
struct PURQ
{
    int n;
    vector<T> sg;
    PURQ() = default;
    PURQ(int n) : n(n), sg(4 * (n + 5)) {}
    
    // to be changed =>> (min , max , sum , gcd , ..)
    T Q(T a, T b){
        return max(a , b);
    }
    void update(int point, T val){
        sg[point+=n-1] = val;
        for (point /= 2; point; point /= 2)
        {
            sg[point] = Q(sg[2 * point], sg[2 * point + 1]);
        }
    }
    T Query(int l, int r){
        int res_l = 0, res_r = 0;
        for (l += n-1 , r += n-1 ; l <= r; l /= 2, r /= 2){
            if (l % 2 != 0)
                res_l = Q(res_l, sg[l++]);
            if (r % 2 == 0)
                res_r = Q(sg[r--], res_r);
        }
        return Q(res_l, res_r);
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