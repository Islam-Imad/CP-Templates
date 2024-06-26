
/*
    DSU (Disjoint Set Union) Data Structure
    1. Union(u,v) : Merge two sets u and v
    2. Get_Leader(u) : Get the leader of the set u belongs to
    3. SameSet(u,v) : Check if u and v belongs to the same set
    4. Get_Size(u) : Get the size of the set u belongs to
    5. CC() : Get the number of connected components
*/


#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct DSU{
    vector<int>Leader,Rank,Gsize;
    int forests;
    DSU(int n){
        forests=n;
        Leader = Rank  = vector<int>(n);
        Gsize=vector<int>(n,1);
        for(int i=0;i<n;++i)Leader[i]=i;
    }
    void Union(int u,int v){
        u=Get_Leader(u),v=Get_Leader(v);
        if(u==v)return;
        if(Rank[u]<Rank[v])swap(u,v);
        Leader[v] = u;
        Gsize[u]+=Gsize[v];
        Rank[u]+=(Rank[u]==Rank[v]);
        --forests;
    }
    bool SameSet(int u,int v){
        return (Get_Leader(v)==Get_Leader(u));
    }
    int Get_Leader(int u){
        return Leader[u]=(Leader[u]==u ? u : Get_Leader(Leader[u]));
    }
    ll Get_Size(int u){
        return Gsize[Get_Leader(u)];
    }
    ll CC(){return forests;}
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