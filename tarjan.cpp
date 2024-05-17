#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

struct SCC {
    int n, cnt,dfs_num;
    vector<vector<int>> adj, dagList;
    vector<int> inStack, lowLink , dfn, comp;
    stack<int> st;
    vector<vector<int>> scc;

    SCC(int n) 
    : n(n)
    , cnt(0)
    , adj(n)
    , inStack(n)
    , lowLink(n)
    , dfn(n, -1)
    , comp(n, -1) 
    , dfs_num(0)
    {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int node){
        inStack[node] = 1;
        for(auto &child:dagList[node]){
            if(!inStack[child]){
                dfs(child);
            }
        }
    }

    void tarjan(int node){
        lowLink[node] = dfn[node] = dfs_num++, inStack[node] = 1;
        st.push(node);
        for(auto &child:adj[node]){
            if(dfn[child]==-1){
                tarjan(child);
                lowLink[node] = min(lowLink[node],lowLink[child]);
            }else if(inStack[child]){
                lowLink[node] = min(lowLink[node],dfn[child]);
            }
        }
        if(lowLink[node]==dfn[node]){
            scc.push_back({});
            while(true){
                int v = st.top();st.pop();
                inStack[v] = 0;
                scc.back().push_back(v);
                comp[v] = cnt;
                if(v==node)break;
            }
            cnt++;
        }
    }

    void get_dag_list(){
        dagList.resize(cnt);
        for(int i=0;i<n;i++){
            for(auto &child:adj[i]){
                if(comp[i]!=comp[child]){
                    dagList[comp[i]].push_back(comp[child]);
                }
            }
        }
    }

    void run(){
        for(int i=0;i<n;i++){
            if(dfn[i]==-1){
                tarjan(i);
            }
        }
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