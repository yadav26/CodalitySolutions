//https://atcoder.jp/contests/dp/tasks/dp_i
//https://github.com/Errichto/youtube/blob/master/atcoder-dp/i.cpp
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<double> dp(N + 1);
    dp[0] = 1;
    for (int coin = 0; coin < N; ++coin) {
        double p_heads;
        cin >> p_heads;

        for (int i = coin+1; i >= 0; --i) {
            dp[i] = (i==0 ? 0: dp[i-1] * p_heads) + dp[i] * (1 - p_heads);
        }
    }

    double ans = 0;
    for (int heads = 0; heads <= N; ++heads ) {
        auto tails = N - heads;
        if (heads > tails)
            ans += dp[heads];
    }
    //printf("%0.10lf\n", and );

std::cout << std::setprecision(10) << std::fixed;
cout << endl << ans;
    return ans;
}