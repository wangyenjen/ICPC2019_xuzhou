#include <bits/stdc++.h>
using namespace std;

const int N = 200006;
const int P = 20;

int lca[P][N];
int sz[N], mx[N];

vector<int> G[N];
vector<int> ans[N];

void dfs(int now, int par) {
    lca[0][now] = par;
    sz[now] = 1;
    mx[now] = 0;
    for (int i: G[now]) {
        if (i == par) continue;
        dfs(i, now);
        sz[now] += sz[i];
        mx[now] = max(mx[now], sz[i]);
    }
}

bool can(int cen, int root) {
    return max(mx[cen], sz[root] - sz[cen]) <= sz[root] / 2;
}

int main () {
    int n; scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1, 1);
    for (int i = 1; i < P; ++i) {
        for (int j = 1; j <= n; ++j) {
            lca[i][j] = lca[i-1][ lca[i-1][j] ];
        }
    }
    for (int i = 1; i <= n; ++i) {
        //consider vertex i can be someone's answer
        int st = i;
        for (int j = P - 1; j >= 0; --j) {
            if (sz[ lca[j][st] ] < 2 * mx[i]) {
                st = lca[j][st];
            }
        }
        if (sz[st] < 2 * mx[i]) st = lca[0][st];
        if (sz[st] < 2 * mx[i]) continue;
        while (can(i, st)) {
            ans[st].push_back(i);
            if (st == 1) break;
            st = lca[0][st];
        }
    }
    for (int i = 1; i <= n; ++i) {
        int m = (int)ans[i].size();
        if (m == 0) {
            puts("-1");
        }
        for (int j = 0; j < m; ++j) {
            printf("%d%c", ans[i][j], " \n"[j == m - 1]);
        }
    }
}

