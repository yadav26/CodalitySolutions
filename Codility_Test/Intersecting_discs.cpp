
//https://app.codility.com/programmers/lessons/6-sorting/number_of_disc_intersections/
//https://www.youtube.com/watch?v=HV8tzIiidSw
// you can use includes, for example:
#include <algorithm>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
#include <vector>
using namespace std;
int solution(vector<int>& A) {
    // Implement your solution here
    vector<int> sv(A.size(), 0);
    vector<int> ev(A.size(), 0);

    if (A.size() < 2) return 0;

    for (int i = 0; i < A.size(); ++i) {
        sv[i] = i - A[i];
        ev[i] = i + A[i];
    }

    sort(sv.begin(), sv.end());
    sort(ev.begin(), ev.end());

    int ans = 0;
    int open = 0;
    for (int i = 0, j = 0; i < sv.size() && j < ev.size();) {
        //cout << " " << sv[i];
        if (sv[i] <= ev[j]) {
            ans += open;
            open += 1;
            ++i;
            continue;
        }
        open = open - 1 >= 0 ? open - 1 : 0;
        ++j;
    }

    return ans > 10000000 ? -1 : ans;
}
