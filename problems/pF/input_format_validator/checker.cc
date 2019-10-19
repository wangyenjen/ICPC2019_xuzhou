#include "testlib.h"
constexpr int T = 10;
constexpr int N = 200;

int main(int argc, char **argv) {
  registerValidation(argc, argv);

  int t = inf.readInt(1, T, "T");
  inf.readEoln();

  for (int i = 0; i < t; i++) {
    inf.readInt(0, N, "N");
    inf.readEoln();
  }
  inf.readEof();
}
