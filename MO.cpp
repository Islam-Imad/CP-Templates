#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

const int N = 1e6 + 5 , SQ = 1e3;

struct query{
    int l, r, idx;
    bool operator<(const query & com) const{
        if(l / SQ != com.l/SQ)
            return l / SQ < com.l / SQ;
        return r < com.r;
    }
};

int lq = 0, rq = -1;

void add(int idx){
    // add idx
}

void remove(int idx){
    // remove idx
}

void slide(int l,int r){
    while(lq < l) remove(lq++);
    while(lq > l) add(--lq);
    while(rq < r) add(++rq);
    while(rq > r) remove(rq--);
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