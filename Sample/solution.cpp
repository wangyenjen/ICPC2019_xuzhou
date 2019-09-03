/**
 * A graph is a tree if and only if
 * 1. m == n - 1, and
 * 2. it is connected.
 */
#include <algorithm>
#include <cstdio>
#include <cassert>
#include <vector>

constexpr int maxn = 1'000'000;

std::vector<int> adj[maxn];
bool visited[maxn];

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v])
            dfs(v);
}

bool check(int n, int m) {
    if (m != n - 1)
        return false;
    dfs(0);
    return std::find(visited, visited + n, false) == visited + n;
}

int main() {
    int n, m;

    int ret = scanf("%d%d", &n, &m);
    assert(ret == 2);
    assert(1 <= n && n <= maxn);
    assert(1 <= m && m <= maxn);

    for (int i = 0; i < m; i++) {
        int u, v;
        int ret = scanf("%d%d", &u, &v);
        assert(ret == 2);
        assert(1 <= u && u <= n);
        assert(1 <= v && v <= n);
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    puts(check(n, m) ? "Yes" : "No");
}
