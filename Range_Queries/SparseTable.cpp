/*
    Sparse Table
    1. Sparse Table is a data structure that allows answering range queries in an array.
    2. It can answer most range queries in O(logn) time.
*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

template<class T=int>
struct sparse_table{
    vector<int>lgs;
    vector<vector<T>>sp;
    int n;
    sparse_table(vector<T>&input_user){
        n = input_user.size();
        sp = vector<vector<T>>(25,vector<T>(n));
        lgs = vector<int>(n+1);
        for(int i=0;i<n;++i)sp[0][i]=input_user[i];
        build();
    }
    T Q(T &com_a , T &com_b){
        return min(com_a,com_b);
    }
    void build(){
        for(int i=2;i<=n;++i)lgs[i]=1+lgs[i/2];

        for(int k = 1;k < 25;++k){
            for(int i=0;(i+(1<<k))<=n;++i){
                sp[k][i]=Q(sp[k-1][i],sp[k-1][i+(1<<(k-1))]);
            }
        }
    }
    T query(int l , int r){
        return Q(sp[lgs[r-l+1]][l],sp[lgs[r-l+1]][r-(1<<lgs[r-l+1])+1]);
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