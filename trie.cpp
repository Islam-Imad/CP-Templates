#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

template<typename T>
struct Trie{
    map<T, Trie*> child;
    bool isEnd;
    Trie(){
        isEnd = false;
    }
    void insert(vector<T> &s){
        Trie* cur = this;
        for(auto &c:s){
            if(!cur->child.count(c)){
                cur->child[c] = new Trie();
            }
            cur = cur->child[c];
        }
        cur->isEnd = true;
    }
    bool search(vector<T> &s){
        Trie* cur = this;
        for(auto &c:s){
            if(!cur->child.count(c)){
                return false;
            }
            cur = cur->child[c];
        }
        return cur->isEnd;
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