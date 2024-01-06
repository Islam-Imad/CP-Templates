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
    DSU D(5);
    
}

int main()
{
ios_base::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    int tc=1;
    // cin>>tc;
    while(tc--){
        solve();
    }
}