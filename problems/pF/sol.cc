/// Author: Wang, Yen-Jen
#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);

  long long ans = 1ll * n * (n + 1) / 2;
  for (int i = 1; i < n; i++) {
    int x;
    scanf("%d", &x);

    ans -= x;
  }

  printf("%lld\n", ans);

  return 0;
}

