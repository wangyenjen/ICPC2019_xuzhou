/// Author: Wang, Yen-Jen
#include "testlib.h"
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  registerValidation(argc, argv);

  int N = inf.readInt(0, 1000000, "N");
  inf.readEoln();

  vector<int> vs;

  for (int i = 1; i < N; i++) {
    int x = inf.readInt(1, N, "x_i");
    if (i == N - 1)
      inf.readEoln();
    else
      inf.readSpace();

    vs.push_back(x);
  }

  sort(vs.begin(), vs.end());

  for (int i = 1; i < N - 1; i++) {
    assert(vs[i] != vs[i - 1]);
  }

  inf.readEof();

  return 0;
}

