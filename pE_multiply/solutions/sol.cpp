#include <cstdio>
#include <random>
#include <algorithm>

const int kN = 100001;

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

long long GCD(long long a, long long b) {
  return !b ? a : GCD(b, a % b);
}

long long Rho(long long N, long long start) {
  long long x = start, y = start, d = 1;
  long long iter = (std::pow(N, .25) + 1) * 10;
  for (int i = 0; i < iter && d == 1; i++) {
    x = ((__int128)x * x + 1) % N;
    y = ((__int128)y * y + 1) % N;
    y = ((__int128)y * y + 1) % N;
    d = GCD(N, x > y ? x - y : y - x);
  }
  if (d == N || d == 1) return -1;
  return d;
}

std::mt19937_64 gen;
using mrand = std::uniform_int_distribution<long long>;

int Decompose(long long N, long long a[]) {
  int sz = 0;
  for (int i : {2, 3, 5, 7}) {
    while (N % i == 0) a[sz++] = i, N /= i;
  }
  long long qu[128];
  int l = 0, r = 0;
  qu[r++] = N;
  while (l < r) {
    long long x = qu[l++];
    if (x == 1) continue;
    if (TestPrime(x)) {
      a[sz++] = x;
      continue;
    }
    for (int i = 0;; i++) {
      long long res = Rho(x, i ? mrand(3, x - 2)(gen) : 2);
      if (res != -1) {
        qu[r++] = res;
        qu[r++] = x / res;
        break;
      }
    }
  }
  return sz;
}

long long Cal(long long N, long long p) {
  long long ans = N;
  for (; N; N /= p) ans -= N % p;
  return ans / (p - 1);
}

struct Pair {
  long long x, y;
  int cnt;
  bool operator<(const Pair& a) const { return y < a.y; }
} p[32];

int main() {
  int T;
  scanf("%d\n", &T);
  while (T--) {
    int N;
    long long X, Y, a;
    scanf("%d%lld%lld", &N, &X, &Y);
    long long c[64];
    int C = Decompose(X, c);
    std::sort(c, c + C);
    int sz = 0;
    p[sz++] = {c[0], 0, 1};
    for (int i = 1; i < C; i++) {
      if (p[sz - 1].x == c[i]) {
        p[sz - 1].cnt++;
      } else {
        p[sz++] = {c[i], 0, 1};
      }
    }
    for (int i = 0; i < sz; i++) p[i].y = Cal(Y, p[i].x);
    for (int i = 0; i < N; i++) {
      scanf("%lld", &a);
      for (int j = 0; j < sz; j++) p[j].y -= Cal(a, p[j].x);
    }
    for (int i = 0; i < sz; i++) p[i].y /= p[i].cnt;
    printf("%lld\n", std::min_element(p, p + sz)->y);
  }
}
