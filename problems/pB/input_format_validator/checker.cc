#include "testlib.h"

#include <cassert>

const int MAX_N = 100000;
const int MAX_B = 100000;
const int MAX_M = 100000;
const int MAX_K = 100000;
const int SUM_K = 100000;


int main(int argc, char** argv) {
  registerValidation(argc, argv);
  int N = inf.readInt(1, MAX_N, "N");
  inf.readSpace();
  int B = inf.readInt(1, MAX_B, "B");
  inf.readSpace();
  int M = inf.readInt(1, MAX_M, "M");
  inf.readEoln();
  for (int i = 1; i <= N; i++) {
    inf.readInt(1, B, "a_i");
    if (i < N) {
      inf.readSpace();
    } else {
      inf.readEoln();
    }
  }
  int sum_k = 0;
  while (M--) {
    int K = inf.readInt(1, MAX_K, "K");
    sum_k += K;
    assert(sum_k <= SUM_K);
    for (int i = 1; i <= K; i++) {
      inf.readSpace();
      int l = inf.readInt(1, N, "l_i");
      inf.readSpace();
      int r = inf.readInt(l, N, "r_i");
    }
    inf.readEoln();
  }
  inf.readEof();
  return 42;
}
