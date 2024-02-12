//https://atcoder.jp/contests/dp/tasks/dp_h
//https://github.com/Errichto/youtube/blob/master/atcoder-dp/h.cpp
#include <iostream>
#include <vector>
using namespace std;
const int modulo = 1e9 + 7;
void add_self(int& a, int b) {
    a += b;
    if (a >= modulo)
        a -= modulo;
}
int main()
{
    int H, W;
    cin >> H;
    cin >> W;
    vector<vector<int>> dp(1005, vector<int>(1005,0));
    vector<vector<char>> s(H+1, vector<char>(W+1));
    
    char ch;
    for (int row = 0; row < H; ++row)
        for (int col = 0; col < W; ++col) {
            cin >> ch;
            s[row][col] = ch;
        }
    dp[0][0] = 1;
    for (int row = 0; row < H; ++row)
        for (int col = 0; col < W; ++col)
        {
            for (auto r2 : { row, row + 1 }) {
                // every next right and bottom squar value to be twice of the current squar
                // 1 1 1
                // 123
                // 123
                int c2 = col;
                if (r2 == row)
                    c2 = col + 1;

                if (r2 < H && c2 < W && s[r2][c2] == '.')
                    add_self(dp[r2][c2], dp[row][col]);
            }

        }

    printf("%d", dp[H - 1][W - 1]);
    return 0;
}
