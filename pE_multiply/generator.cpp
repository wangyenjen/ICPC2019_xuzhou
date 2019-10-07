#include <cstdio>
#include <string>
#include <random>
#include <algorithm>

#include <randdist.h>

using namespace CompLib;

std::mt19937_64 gen;
typedef UniformIntDistribution<long long> mrand;
typedef UniformRealDistribution<long double> rrand;

const int kN = 100000, kT = 8;
const long long kY = 1'000'000'000'000'000'000;

double x[kN];

long long Pow(long long x, long long y, long long P) {
  long long ans = 1;
  for (; y; y >>= 1) {
    if (y & 1) ans = (__int128)ans * x % P;
    x = (__int128)x * x % P;
  }
  return ans;
}

bool TestPrime(long long N) {
  if (N == 2) return true;
  if (N < 2 || N % 2 == 0) return false;
  long long u = N - 1;
  while (u % 2 == 0) u >>= 1;
  for (long long a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
    long long x = Pow(a % (N - 1) + 1, u, N);
    for (long long i = u; i < N; i <<= 1) {
      long long y = (__int128)x * x % N;
      if (y == 1 && x != 1 && x != N - 1) return false;
      x = y;
    }
    if (x != 1) return false;
  }
  return true;
}

long long GenPrime(long long l, long long r) {
  long long x = mrand(l, r)(gen);
  while (!TestPrime(x)) x = mrand(l, r)(gen);
  return x;
}

long long GetX(int t, long long M) {
  if (t == 5) return GenPrime(2, 11);
  if (t >= 6) {
    long long ans = 1;
    long long x[4];
    for (int i = 0; i < 4; i++) x[i] = GenPrime(2, 60);
    while (true) {
      long long s = x[mrand(0, 3)(gen)];
      long long p;
      if (__builtin_smulll_overflow(s, ans, &p) || p > M) break;
      ans *= s;
    }
    return ans;
  }
  t++;
  long long T = std::pow((double)M, 1. / t);
  long long ans = 1;
  for (int i = 0; i < t - 1; i++) {
    long long s = GenPrime(T * 0.3, T * 2);
    ans *= s;
    M /= s;
  }
  ans *= GenPrime(M * 0.8, M);
  return ans;
}

int main(int argc, char** argv) {
  if (argc < 3) return 1;
  int mN = std::stoi(argv[1]);
  long long mX = std::stoll(argv[2]);
  printf("%d\n", kT);
  for (int t = 0; t < kT; t++) {
    int N = mrand(mN * 2 / 3, mN)(gen);
    long long X = GetX(t, mX);
    long long Y = rrand(1, kY)(gen);
    printf("%d %lld %lld\n", N, X, Y);
    long long pY = rrand(Y / 2, Y - 1)(gen);
    double sum = 0;
    for (int i = 0; i < N; i++) sum += x[i] = rrand(0, 1)(gen);
    for (int i = 0; i < N; i++) {
      printf("%lld%c", (long long)(x[i] / sum * pY) + mrand(-1000, 1000)(gen),
          " \n"[i == N - 1]);
    }
  }
}
