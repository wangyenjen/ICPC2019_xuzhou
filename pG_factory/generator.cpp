#include <cstdio>
#include <string>
#include <random>
#include <algorithm>

#include <randdist.h>

using namespace CompLib;

std::mt19937_64 gen;
typedef UniformIntDistribution<int> mrand;

const int kN = 20000, kD = 50, kL = 100;

int x[kN][kD];
int perm[kD];

int main(int argc, char** argv) {
  if (argc < 4) return 1;
  int N = std::stoi(argv[1]), D = std::stoi(argv[2]), mode = std::stoi(argv[3]);
  gen.seed(HashArgs(argc, argv));

  if (mode < 2) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < D; j++) x[i][j] = mrand(1, kL)(gen);
      if (mode == 1) std::sort(x[i], x[i] + D);
    }
  } else if (mode == 2) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < D; j++) x[i][j] = mrand(kL - 5, kL)(gen);
      x[i][mrand(0, D - 1)(gen)] = 1;
    }
  }
  for (int i = 0; i < D; i++) perm[i] = i;
  Shuffle(perm, perm + D, gen);
  printf("%d %d\n", N, D);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < D; j++) printf("%d%c", x[i][perm[j]], " \n"[j == D - 1]);
  }
}
