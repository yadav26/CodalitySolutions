//https://atcoder.jp/contests/dp/tasks/dp_g
//https://github.com/Errichto/youtube/blob/master/atcoder-dp/g.cpp
#include <iostream>
#include <vector>
using namespace std;
const int nax = 1e5 + 5;
vector<int> edges[nax];
bool visited[nax];
int dist[nax];
int in_degree[nax];
void dfs(int a)
{
    visited[a] = true;
    for (int b : edges[a])
    {
        dist[b] = max(dist[b], dist[a] + 1);
        --in_degree[b];
        if (in_degree[b] == 0)
            dfs(b);
    }
} // dfs end
void dag_atcoder()
{
    int n, e, a, b;
//    scanf("%d%d", &n, &e);
    cin >> n;
    cin >> e;

    while (e--)
    {
        //scanf("%d%d", &a, &b);
        cin >> a;
        cin >> b;
        edges[a].push_back(b);
        ++in_degree[b];
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!visited[i] && in_degree[i] == 0)
        {
            dfs(i);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, dist[i]);

    printf("%d", ans);
}

int main(){
dag_atcoder();
return 0;
}