#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
const int mod = 998244353;
ll dp[maxn];
ll dp2[maxn][70];
void add(ll &a, ll b) {
  a += b;
  if (a >= mod)
    a -= mod;
}
void pre() {
  dp[0] = 0, dp[1] = 1, dp[2] = 2, dp[3] = 4;
  for (int i = 4; i < maxn; i++) {
    dp[i] = (2 * dp[i - 1] - dp[i - 2] + dp[i - 3] - dp[i - 4] + 1) % mod;
    if (dp[i] < 0)
      dp[i] += mod;
  }
  dp2[3][16 + 8 + 4 + 1] = dp2[3][32 + 16 + 2 + 1] = dp2[3][32 + 8 + 4 + 2] = 2;
  for (int i = 3; i < maxn - 1; i++) {
    for (int j = 0; j < 64; j++)
      if (dp2[i][j]) {
        int pos[6];
        for (int k = 0; k < 6; k++)
          pos[k] = (1 + (j & (1 << k))) >> 1;
        if (pos[0])
          add(dp2[i + 1][pos[1] + pos[2] + pos[4] + 4], dp2[i][j]);
        if (pos[1])
          add(dp2[i + 1][pos[2] + pos[4] + 36], dp2[i][j]);
        if (pos[2])
          add(dp2[i + 1][pos[1] + pos[4] + 20], dp2[i][j]);
        if (pos[3])
          add(dp2[i + 1][pos[1] + pos[2] + pos[4] + 32], dp2[i][j]);
        if (pos[4])
          add(dp2[i + 1][pos[1] + pos[2] + 48], dp2[i][j]);
        if (pos[5])
          add(dp2[i + 1][pos[1] + pos[2] + pos[4] + 16], dp2[i][j]);
      }
  }
}
int main() {
  pre();
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    if (n == 1)
      puts("1");
    else if (n == 2 || k == 1)
      puts("2");
    else if (k == 2)
      printf("%lld\n", (2 * (dp[n] - dp[n - 1] + dp[n - 2] + mod)) % mod);
    else {
      ll ans = 0;
      for (int i = 0; i < 64; i++)
        add(ans, dp2[n][i]);
      printf("%lld\n", ans);
    }
  }
  return 0;
}
