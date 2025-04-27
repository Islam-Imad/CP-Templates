#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define X first
#define Y second

vector<int> compute_prefix(const string &pat){
    int n = pat.size();
    vector<int> lps(n);
    for(int i = 1,k = 0;i < n ; ++i){
        while(k > 0 && pat[i] != pat[k]){
            k = lps[k-1];
        }
        if(pat[i] == pat[k]){
            ++k;
        }
        lps[i] = k;
    }
    return lps;
}

vector<vector<int>> compute_prefix_2(const string &pat)
{
	int n = pat.size();
	vector<vector<int>> dp(n, vector<int>(26, 0));
	vector<int> lps(n);
	for (int i = 1, k = 0; i < n; ++i)
	{
		while (k > 0 && pat[i] != pat[k])
		{
			k = lps[k - 1];
		}
		if (pat[i] == pat[k])
		{
			++k;
		}
		lps[i] = k;
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < 26; ++j)
		{
			if (pat[i] != 'a' + j)
			{
				dp[i][j] = dp[lps[i - 1]][j];
			}
			else
			{
				dp[i][j] = i;
			}
		}
	}
	return dp;
}

int KMP(const string &str,const string &pat){
    int n = str.size(),m = pat.size(), ret = 0;
    vector<int> lps = compute_prefix(pat);
    for(int i = 0,k = 0;i < n ; ++i){
        while(k > 0 && str[i] != pat[k]){
            k = lps[k-1];
        }
        if(str[i] == pat[k]){
            ++k;
        }
        if(k == m){
            ret++;
            k = lps[k-1];
        }
    }
    return ret;
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