#include <bits/stdc++.h>
using namespace std;
#define P 44700
bool p[P];
vector<int> pset;
void build() {
  for (int i = 1; i < P; i++)
    p[i] = true;
  for (int i = 2; i < P; i++)
    if (p[i]) {
      pset.push_back(i);
      for (int j = i + i; j < P; j += i)
        p[j] = false;
    }
}
bool isp(int x) {
  if (x < P)
    return p[x];
  for (int i : pset) {
    if (i * i > x)
      break;
    if (x % i == 0)
      return false;
  }
  return true;
}
int l, r;
bool le3() {
  if (r - l + 1 > 300)
    return true;
  int cnt = 0;
  for (int i = l; i <= r; i++)
    if (isp(i))
      cnt++;
  return 3 * cnt < r - l + 1;
}
int main() {
  build();
  int T;
  scanf("%d", &T);
  assert(1 <= T and T <= 100);
  while (T--) {
    scanf("%d%d", &l, &r);
    assert(1 <= l and l <= r and r <= 1000000000);
    puts(le3() ? "Yes" : "No");
  }
}
