// Author: Yen-Jen Wang
#include "testlib.h"

const int MAX_T = 100000;
const int MAX_N = 1000000;

int main(int argc, char** argv) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, MAX_T, "T");
  inf.readEoln();
  while (T--) {
    inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    inf.readInt(1, 3, "K");
    inf.readEoln();
  }
  inf.readEof();
  return 42;
}
