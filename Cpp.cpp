#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T=int>
using Tree = tree <T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

ll modpow(ll base,ll exp , ll mod){
    base%=mod;
    ll res = 1;
    while(exp){
        if(exp&1)res = res*base%mod;
        base = base*base%mod, exp>>=1;
    }
    return res;
}

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
/*
  // bash script to create files from a to n and copy template file into each file created
    for i in {a..n}; do touch $i.cpp ; done
    for i in {a..n}; do cp template.cpp $i.cpp ; done
*/
