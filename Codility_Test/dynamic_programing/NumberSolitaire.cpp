#include <vector>
using namespace std;

vector<int> dp(100009, -1);

//https://app.codility.com/demo/results/training9ANMTD-ENJ/
int numsol(int i, int k, std::vector<int>& A) {
    if (i == 0)
        return dp[i]=A[0];

    if (dp[i] != -1)
        return dp[i];

    int sum = -999999999;
    for (int j = k; j >= 1; --j) 
        if (i - j >= 0)
            sum = max(sum, numsol(i - j, k, A) + A[i]);
    
    return dp[i] = sum;
}

int solution(vector<int> &A) {
    auto ans = numsol(A.size()-1, 6, A);
    return ans;
}