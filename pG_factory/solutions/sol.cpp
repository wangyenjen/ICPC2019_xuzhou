#include <array>
#include <cmath>
#include <cstdio>
#include <random>
#include <algorithm>

const int kN = 50001, kD = 50;

using Data = double;

std::mt19937 gen;
std::array<Data, kD> d[50003];
int N, D;

Data F(Data x[]) {
  const int tD = D - 1;
  x[tD] = 1;
  for (int i = 0; i < tD; i++) x[tD] -= x[i];
  Data sum = 0;
  for (int i = 0; i < N; i++) {
    Data mn = x[tD] * d[i][tD];
    for (int j = 0; j < tD; j++) mn = std::min(mn, x[j] * d[i][j]);
    sum += mn;
  }
  return sum;
}

void Epoch(Data x[], Data eta, int M, Data p) {
  static Data vx[kD] = {};
  const int tD = D - 1;
  for (int j = 0; j <= N - M; j += M) {
    x[tD] = 1;
    for (int i = 0; i < tD; i++) x[tD] -= x[i];
    Data sum[kD] = {};
    for (int i = j; i < j + M; i++) {
      Data mn = x[tD] * d[i][tD];
      int id = tD;
      for (int k = 0; k < tD; k++) {
        if (x[k] * d[i][k] < mn) mn = x[k] * d[i][k], id = k;
      }
      if (id == tD) {
        for (int k = 0; k < tD; k++) sum[k] -= d[i][tD];
      } else {
        sum[id] += d[i][id];
      }
    }
    Data tot = 0;
    for (int k = 0; k < tD; k++) sum[k] /= M, tot += sum[k] * sum[k];
    tot = 1 / (std::sqrt(tot) + 1);
    for (int k = 0; k < tD; k++) {
      vx[k] = vx[k] * p + sum[k] * tot;
      x[k] += vx[k] * eta;
    }
  }
  std::shuffle(d, d + N, gen);
}

int main() {
  scanf("%d%d", &N, &D);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < D; j++) scanf("%lf", &d[i][j]);
  }
  int E = 4000000 / N, B = std::min(100, N);
  Data x[kD];
  for (int i = 0; i < D; i++) x[i] = 1. / D;
  for (int i = 0; i < E; i++) {
    Data eta = std::pow(1e-4, (Data)i / E) * 3e-2;
    Epoch(x, eta, B, 0.99);
  }
  printf("%.9lf\n", F(x));
}
