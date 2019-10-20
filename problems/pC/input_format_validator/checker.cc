// Author: Yen-Jen Wang
#include "testlib.h"

int main(int argc, char** argv) {
  registerValidation(argc, argv);
  int T = inf.readInt(1, 100, "T");
  inf.readEoln();
  while (T--) {
    int l = inf.readInt(1, 1000000000, "L");
    inf.readSpace();
    inf.readInt(l, 1000000000, "R");
    inf.readEoln();
  }
  inf.readEof();
  return 42;
}
