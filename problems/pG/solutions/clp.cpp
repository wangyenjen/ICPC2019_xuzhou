#include <cstdio>
#include <cstdlib>
#include <coin/ClpSimplex.hpp>

const int kN = 20000, kD = 50;
int x[kN][kD];

int main() {
  int N, D;
  scanf("%d%d", &N, &D);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < D; j++) scanf("%d", x[i] + j);
  }
  char filename[] = "AXXXXXX.mps";
  close(mkstemps(filename, 4));
  FILE* f = fopen(filename, "w");
  fprintf(f, "NAME          TESTPROB\n");
  fprintf(f, "ROWS\n");
  fprintf(f, " N  COST\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < D; j++) {
      fprintf(f, " L  X%05d%02d\n", i, j);
    }
  }
  fprintf(f, " L  LAST\n");
  fprintf(f, "COLUMNS\n");
  for (int j = 0; j < D; j++) {
    for (int i = 0; i < N; i++) {
      fprintf(f, "    P%02d       X%05d%02d  %12d\n", j, i, j, x[i][j]);
    }
    fprintf(f, "    P%02d       LAST                -1\n", j);
  }
  for (int i = 0; i < N; i++) {
    fprintf(f, "    Q%05d    COST      %12d\n", i, 1);
    for (int j = 0; j < D; j++) {
      fprintf(f, "    Q%05d    X%05d%02d  %12d\n", i, i, j, 1);
    }
  }
  fprintf(f, "RHS\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < D; j++) {
      fprintf(f, "    RHS1      X%05d%02d  %12d\n", i, j, 0);
    }
  }
  fprintf(f, "    RHS1      LAST      %12d\n", 1);
  fprintf(f, "BOUNDS\n");
  for (int j = 0; j < D; j++) fprintf(f, " FR BND1      P%02d\n", j);
  for (int i = 0; i < N; i++) fprintf(f, " FR BND1      Q%05d\n", i);
  fprintf(f, "ENDATA\n");
  fclose(f);

  ClpSimplex model;
  CoinMessageHandler handler(stderr);
  model.passInMessageHandler(&handler);
  model.readMps(filename);
  model.setOptimizationDirection(-1); // maximize
  model.primal();
  printf("%.7lf\n", model.objectiveValue());

  remove(filename);
}
