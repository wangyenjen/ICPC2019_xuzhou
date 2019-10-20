#include <bits/stdc++.h>
using namespace std;
#define T 100
#define MX 1000000000
mt19937 rng(880301);
bool isp(int x) {
  for (int i = 2; i * i <= x; i++)
    if (x % i == 0)
      return false;
  return true;
}
int randint(int lb, int ub) {
  return uniform_int_distribution<int>(lb, ub)(rng);
}
int randp(int lb, int ub) {
  int x = randint(lb, ub);
  while (!isp(x))
    x = randint(lb, ub);
  return x;
}
vector<pair<int, int>> tests;
#define N 10000
typedef long long LL;
int p[N];
bool le(pair<int, int> p1, pair<int, int> p2) {
  int pp1 = p[p1.second] - p[p1.first - 1];
  int ln1 = p1.second - p1.first + 1;
  int pp2 = p[p2.second] - p[p2.first - 1];
  int ln2 = p2.second - p2.first + 1;
  return (LL)pp1 * ln2 < (LL)pp2 * ln1;
}
bool gr(pair<int, int> p1, pair<int, int> p2) {
  int pp1 = p[p1.second] - p[p1.first - 1];
  int ln1 = p1.second - p1.first + 1;
  int pp2 = p[p2.second] - p[p2.first - 1];
  int ln2 = p2.second - p2.first + 1;
  return (LL)pp1 * ln2 > (LL)pp2 * ln1;
}
void special() {
  for (int i = 1; i < N; i++) {
    if (isp(i))
      p[i] = 1;
    p[i] += p[i - 1];
  }
  vector<pair<int, int>> cand;
  for (int i = 1; i < N; i++)
    for (int j = i; j < N; j++) {
      int tp = p[j] - p[i - 1];
      if (3 * tp < (j - i + 1)) {
        cand.push_back({i, j});
        if (cand.size() > 10u) {
          sort(cand.begin(), cand.end(), gr);
          cand.resize(10);
        }
      }
    }
  for (auto x : cand)
    tests.push_back(x);
  cand.clear();
  for (int i = 1; i < N; i++)
    for (int j = i; j < N; j++) {
      int tp = p[j] - p[i - 1];
      if (3 * tp >= (j - i + 1)) {
        cand.push_back({i, j});
        if (cand.size() > 10u) {
          sort(cand.begin(), cand.end(), le);
          cand.resize(10);
        }
      }
    }
  for (auto x : cand)
    tests.push_back(x);
}
void uniq() {
  sort(tests.begin(), tests.end());
  tests.resize(unique(tests.begin(), tests.end()) - tests.begin());
}
int main() {
  for (int i = 1; i <= 10; i++)
    for (int j = i; j <= 10; j++)
      tests.push_back({i, j});
  for (int lb : {1, 2})
    for (int ub : {MX - 1, MX})
      tests.push_back({lb, ub});
  special();
  for (int i = 0; i < 3; i++) {
    int x = randp(1e6, 1e9 - 1);
    for (int j = -1; j <= 1; j++)
      tests.push_back({x + j, x + j});
  }
  for (auto sample : {make_pair(7, 7), make_pair(25, 25), make_pair(5, 14)})
    tests.push_back(sample);
  uniq();
  while ((int)tests.size() < T) {
    int lb = randint(1, 1e9);
    int ub = randint(1, 1e9);
    if (lb > ub)
      swap(lb, ub);
    tests.push_back({lb, ub});
    uniq();
  }
  shuffle(tests.begin(), tests.end(), rng);
  printf("%d\n", T);
  for (auto i : tests)
    printf("%d %d\n", i.first, i.second);
}
