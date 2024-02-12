//https://atcoder.jp/contests/dp/tasks/dp_s
//https://github.com/Errichto/youtube/blob/master/atcoder-dp/s.cpp


#include <string>
#include <vector>
#include <iostream>

using namespace std;

void digitsum_gaandu()
{
    //Find the number of integers between 
    /*1 and
        K(inclusive) satisfying the following condition, modulo
        10 pow 9 + 7:
    The sum of the digits in base ten is a multiple of  D.*/
    //
    string s;
    int k;
    cin >> s >> k;

    vector<vector<int>> dp(k, vector<int>(2));
    dp[0][0] = 1;
    for (int where = 0; where < s.size(); ++where) {
        vector<vector<int>> new_dp(k, vector<int>(2));
        for (int sum = 0; sum < k; ++sum) {
            for (auto smaller_already : { false,true }){
                for (int digit = 0; digit < 10; ++digit) {
                    if (digit > s[where] - '0' && !smaller_already)
                        break;
                    add_self(new_dp[(sum + digit) % k][smaller_already || (digit < s[where] - '0')], dp[sum][smaller_already]);
                }
            }
        }

        cout << endl;
        for (int sum = 0; sum < k; ++sum) 
            cout << "[" << new_dp[sum][0] << ":" << new_dp[sum][1] << "] ";

        dp = new_dp;
    }
    int ans = (dp[0][false] + dp[0][true]) % modulo;
    cout << "\nans = " << ans;
    
}
