// Author: Yen-Jen Wang
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const int MAX_N = 1000000 + 7;

ll a[MAX_N];
ll b[MAX_N];

ll get_next(int n) { // for n > 20;
  ll ans = 3 * a[n - 1] - 4 * a[n - 3] + 3 * a[n - 4] - 4 * a[n - 5] -
           9 * a[n - 6] + 2 * a[n - 7] + 5 * a[n - 8] + 9 * a[n - 9] +
           17 * a[n - 10] + 16 * a[n - 11] + 14 * a[n - 12] + 8 * a[n - 13] -
           2 * a[n - 14] - 5 * a[n - 15] - 5 * a[n - 16] - 6 * a[n - 17] -
           4 * a[n - 18] - a[n - 19];
  ans %= MOD;
  if (ans < 0) {
    ans += MOD;
  }
  return ans;
}

int main() {
  a[0] = 1;
  a[1] = 1;
  a[2] = 2;
  a[3] = 6;
  a[4] = 24;
  a[5] = 72;
  a[6] = 180;
  a[7] = 428;
  a[8] = 1042;
  a[9] = 2512;
  a[10] = 5912;
  a[11] = 13592;
  a[12] = 30872;
  a[13] = 69560;
  a[14] = 155568;
  a[15] = 345282;
  a[16] = 761312;
  a[17] = 1669612;
  a[18] = 3645236;
  a[19] = 7927404;
  a[20] = 17180092;
  for (int i = 21; i < MAX_N; i++) {
    a[i] = get_next(i);
  }

  b[0] = 1;
  b[1] = 1;
  b[2] = 1;
  b[3] = 3;
  b[4] = 6;
  for (int i = 5; i < MAX_N; i++) {
    b[i] = 3 * b[i - 1] - 3 * b[i - 2] + 2 * b[i - 3] - 2 * b[i - 4] + b[i - 5];
    b[i] %= MOD;
    if (b[i] < 0) {
      b[i] += MOD;
    }
  }

  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    if (n == 1) {
      printf("%d\n", 1);
      continue;
    } else if (k == 1) {
      puts("2");
    } else if (k == 2) {
      printf("%lld\n", b[n] * 2 % MOD);
    } else { // k == 3
      printf("%lld\n", a[n]);
    }
  }
  return 0;
}
