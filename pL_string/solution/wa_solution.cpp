#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>

const int N = 300000 + 10, M = 20;

int fa[M][N], sa[N], rk[M][N];
int ht[N], depth[N], parent[N];
int y[N], ts[N], cnt[N];
char s[N];

int main() {
  int n, q;
  scanf("%d%d%s", &n, &q, s);
  for (int i = 0; i < n; ++i) {
    fa[0][i] = i;
    rk[0][i] = s[i] - 'A';
    cnt[s[i] - 'A']++;
  }
  for (int i = 1; i < 26; ++i) cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; ++i) sa[--cnt[s[i] - 'A']] = i;
  depth[0] = 1;
  parent[0] = -1;
  for (int i = 1; i < n; ++i) {
    scanf("%d", &parent[i]);
    --parent[i];
    depth[i] = depth[parent[i]] + 1;
  }
  for (int k = 1; k < M; ++k) {
    for (int i = 0; i < n; ++i) {
      int go = fa[k - 1][i];
      if (go != -1 && parent[go] != -1) {
        fa[k][i] = fa[k - 1][parent[go]];
        y[i] = rk[k - 1][parent[go]] + 1;
      } else {
        fa[k][i] = -1;
        y[i] = 0;
      }
    }
    int* x = rk[k - 1], *r = rk[k];
    memset(cnt, 0, sizeof(int) * (n + 1));
    for (int i = 0; i < n; ++i) cnt[y[i]]++;
    for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i) ts[--cnt[y[i]]] = i;
    memset(cnt, 0, sizeof(int) * n);
    for (int i = 0; i < n; ++i) cnt[x[i]]++;
    for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i) sa[--cnt[x[ts[i]]]] = ts[i];
    r[sa[0]] = 0;
    for (int i = 0; i + 1 < n; ++i) {
      r[sa[i + 1]] = r[sa[i]] + (x[sa[i]] != x[sa[i + 1]] || y[sa[i]] != y[sa[i + 1]]);
    }
  }
  for (int i = 1; i < n; ++i) {
    int x = sa[i - 1], y = sa[i];
    if (rk[M - 1][x] == rk[M - 1][y]) {
      ht[i] = depth[y];
      continue;
    }
    if (s[x] != s[y]) {
      ht[i] = 0;
      continue;
    }
    int k = 0;
    while (k < M && rk[k][x] == rk[k][y]) ++k;
    --k;
    int ret = 1 << k;
    x = parent[fa[k][x]];
    y = parent[fa[k][y]];
    for (; k >= 0; --k) {
      if (x != -1 && y != -1 && rk[k][x] == rk[k][y]) {
        ret += (1 << k);
        x = parent[fa[k][x]];
        y = parent[fa[k][y]];
      }
    }
    ht[i] = ret;
  }
  int *lg = y;
  lg[0] = -1;
  for (int i = 1; i < n; ++i) lg[i] = lg[i >> 1] + 1;
  for (int i = 0; i < n; ++i) rk[0][i] = ht[i];
  for (int j = 1; (1 << j) <= n; ++j) {
    for (int i = 0; i + (1 << j) <= n; ++i) {
      rk[j][i] = std::min(rk[j - 1][i], rk[j - 1][i + (1 << (j - 1))]);
    }
  }
  auto ask = [&](int x, int y) {
    int k = lg[y - x + 1];
    return std::min(rk[k][x], rk[k][y - (1 << k) + 1]);
  };

  for (int i = 0; i < q; ++i) {
    int x, l;
    scanf("%d%d", &x, &l);
    x = rk[M - 1][x - 1];
    int left = 0, right = x;
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      int len = mid == x ? l : ask(mid + 1, x);
      if (len >= l) right = mid;
      else left = mid + 1;
    }
    int low = left;
    /*int low = x;
    for (int i = x, h = l; i >= 0; --i) {
      h = std::min(h, ht[i]);
      if (h >= l) low = i - 1;
      else break;
    }
    assert(low == left);*/
    left = x, right = n - 1;
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      int len = x == mid ? l : ask(x + 1, mid);
      if (len >= l) left = mid;
      else right = mid - 1;
    }
    int high = left;
    /*int high = x;
    for (int i = x + 1, h = l; i < n; ++i) {
      h = std::min(h, ht[i]);
      if (h >= l) high = i;
      else break;
    }
    assert(high == left);*/
    printf("%d\n", high - low + 1);
  }
  return 0;
}
