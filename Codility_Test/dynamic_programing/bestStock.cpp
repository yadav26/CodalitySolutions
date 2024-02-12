#include <bits/stdc++.h>

using namespace std;

int solution_beststock(vector<int>& A) {
    int n = A.size();

    vector < pair<int, int> > dp(n + 1, { -INF ,-INF });
    //dp[i] - for i th day the max future value for that day, and the difference 
    dp[n].first = 0;
    for (int i = n-1; i >= 0; --i) {
        for (int j = i + 1; j < i+2; ++j) {
            dp[i].first = max(dp[j].first, A[i]);
            dp[i].second = dp[i].first - A[i];
        }
    }
    int ans = -INF;
    for (int i = 0; i < n - 1; ++i)
        if (dp[i].second > ans)
            ans = dp[i].second;

    return ans;
}