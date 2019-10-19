#include <bits/stdc++.h>
using namespace std;
constexpr int T = 10;
constexpr int N = 200;
vector<int> hard = {87, 108, 51, 102, 111, 138, 150, 159};
int main() {
  vector<int> v;
  for (int i = 0; i <= N; ++i) {
    v.push_back(i);
  }
  for (int i = N + 1; i < T * 25; ++i) {
    v.push_back(hard[rand() % (int)hard.size()]);
  }
  random_shuffle(v.begin(), v.end());
  for (int _ = 0; _ < 25; ++_) {
    char fname[64];
    sprintf(fname, "testdata/%02d.in", _);
    FILE *f = fopen(fname, "w");
    fprintf(f, "%d\n", T);
    for (int i = 0; i < T; ++i) {
      fprintf(f, "%d\n", v[_ * T + i]);
    }
    fclose(f);
  }
  for (int _ = 25; _ < 27; ++_) {
    int K = (_ == 25 ? 4 : (int)hard.size());
    char fname[64];
    sprintf(fname, "testdata/%02d.in", _);
    FILE *f = fopen(fname, "w");
    fprintf(f, "%d\n", T);
    for (int i = 0; i < T; ++i) {
      fprintf(f, "%d\n", hard[i % K]);
    }
    fclose(f);
  }
}
