#include <stdio.h>
const int N = 1e6 + 10;
const int MOD = 998244353;
long long ans[4][N], dp[N][27];
void one() {
  ans[1][1] = 1;
  for (int i = 2; i < N; i++)
    ans[1][i] = 2;
  return;
}
void two() {
  ans[2][1] = 1;
  ans[2][2] = 2;
  ans[2][3] = 6;
  ans[2][4] = 12;
  dp[4][0] = 2;  // 12x to 0 1
  dp[4][1] = 1;  // 21x to 10 4
  dp[4][2] = 1;  // 1x2 to 0 3
  dp[4][3] = 1;  // 2x1 to 2 9
  dp[4][4] = 1;  // x12x to 5
  dp[4][5] = 1;  // x21x to 4
  dp[4][6] = 0;  // x1x2 to 7
  dp[4][7] = 1;  // x2x1 to 9
  dp[4][8] = 1;  // x12 to 5 7
  dp[4][9] = 2;  // x21 to 8 9
  dp[4][10] = 1; // 1x2x to 0
  dp[4][11] = 0; // 2x1x to 10
  for (int i = 5; i < N; i++) {
    dp[i][0] = (dp[i - 1][0] + dp[i - 1][2] + dp[i - 1][10]) % MOD;
    dp[i][1] = dp[i - 1][0];
    dp[i][2] = dp[i - 1][3];
    dp[i][3] = dp[i - 1][2];
    dp[i][4] = (dp[i - 1][1] + dp[i - 1][5]) % MOD;
    dp[i][5] = (dp[i - 1][4] + dp[i - 1][8]) % MOD;
    dp[i][7] = (dp[i - 1][6] + dp[i - 1][8]) % MOD;
    dp[i][8] = dp[i - 1][9];
    dp[i][9] = (dp[i - 1][3] + dp[i - 1][7] + dp[i - 1][9]) % MOD;
    dp[i][10] = dp[i - 1][1];
    ans[2][i] = 0;
    for (int j = 0; j < 12; j++)
      ans[2][i] += dp[i][j];
    ans[2][i] %= MOD;
  }
  return;
}
void three() {
  ans[3][1] = 1;
  ans[3][2] = 2;
  ans[3][3] = 6;
  ans[3][4] = 24;
  ans[3][5] = 72;
  ans[3][6] = 180;
  dp[6][0] = 4;   // x12x3x or x21x3x to 21
  dp[6][1] = 8;   // 3x12x or 3x21x to 8 21
  dp[6][2] = 8;   // x123x to 21 17
  dp[6][3] = 4;   // 321x to 8 17 21
  dp[6][4] = 8;   // 21x3x to 25 22
  dp[6][5] = 4;   // 21x3 to 25 22 9
  dp[6][6] = 2;   // 1x2x3x to 12
  dp[6][7] = 2;   // 1x2x3 to 12 10
  dp[6][8] = 10;  // 1x23x or 1x32x to 12 18
  dp[6][9] = 2;   // 1x23 to 12 18 10
  dp[6][10] = 4;  // 1x3x2 to 13 26
  dp[6][11] = 4;  // 1x32 to 13 19 26
  dp[6][12] = 16; // 12x3x to 14 23
  dp[6][13] = 8;  // 12x3 to 14 23 11
  dp[6][14] = 12; // 123x to 14 23 20
  dp[6][15] = 2;  // x31x2x to 0
  dp[6][16] = 2;  // 31x2x to 6 0
  dp[6][17] = 4;  // x231x to 15 0
  dp[6][18] = 10; // 2x13x or 2x31x to 24 1
  dp[6][19] = 2;  // 31x2 to 7 1 24
  dp[6][20] = 4;  // 231x to 24 16 1
  dp[6][21] = 16; // x213x to 21 2
  dp[6][22] = 8;  // 312x to 8 2 21
  dp[6][23] = 12; // 213x to 25 22 3
  dp[6][24] = 8;  // 13x2x to 12 4
  dp[6][25] = 8;  // 132x to 12 4 18
  dp[6][26] = 8;  // 13x2 to 13 5 26
  for (int i = 7; i < N; i++) {
    dp[i][0] = (dp[i - 1][15] + dp[i - 1][16] + dp[i - 1][17]) % MOD;
    dp[i][1] = (dp[i - 1][18] + dp[i - 1][19] + dp[i - 1][20]) % MOD;
    dp[i][2] = (dp[i - 1][21] + dp[i - 1][22]) % MOD;
    dp[i][3] = (dp[i - 1][23]) % MOD;
    dp[i][4] = (dp[i - 1][24] + dp[i - 1][25]) % MOD;
    dp[i][5] = (dp[i - 1][26]) % MOD;
    dp[i][6] = (dp[i - 1][16]) % MOD;
    dp[i][7] = (dp[i - 1][19]) % MOD;
    dp[i][8] = (dp[i - 1][1] + dp[i - 1][3] + dp[i - 1][22]) % MOD;
    dp[i][9] = (dp[i - 1][5]) % MOD;
    dp[i][10] = (dp[i - 1][7] + dp[i - 1][9]) % MOD;
    dp[i][11] = (dp[i - 1][13]) % MOD;
    dp[i][12] = (dp[i - 1][6] + dp[i - 1][7] + dp[i - 1][8] + dp[i - 1][9] +
                 dp[i - 1][24] + dp[i - 1][25]) %
                MOD;
    dp[i][13] = (dp[i - 1][10] + dp[i - 1][11] + dp[i - 1][26]) % MOD;
    dp[i][14] = (dp[i - 1][12] + dp[i - 1][13] + dp[i - 1][14]) % MOD;
    dp[i][15] = (dp[i - 1][17]) % MOD;
    dp[i][16] = (dp[i - 1][20]) % MOD;
    dp[i][17] = (dp[i - 1][2] + dp[i - 1][3]) % MOD;
    dp[i][18] = (dp[i - 1][8] + dp[i - 1][9] + dp[i - 1][25]) % MOD;
    dp[i][19] = (dp[i - 1][11]) % MOD;
    dp[i][20] = (dp[i - 1][14]) % MOD;
    dp[i][21] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3] +
                 dp[i - 1][21] + dp[i - 1][22]) %
                MOD;
    dp[i][22] = (dp[i - 1][4] + dp[i - 1][5] + dp[i - 1][23]) % MOD;
    dp[i][23] = (dp[i - 1][12] + dp[i - 1][13] + dp[i - 1][14]) % MOD;
    dp[i][24] = (dp[i - 1][18] + dp[i - 1][19] + dp[i - 1][20]) % MOD;
    dp[i][25] = (dp[i - 1][4] + dp[i - 1][5] + dp[i - 1][23]) % MOD;
    dp[i][26] = (dp[i - 1][10] + dp[i - 1][11] + dp[i - 1][26]) % MOD;
    ans[3][i] = 0;
    for (int j = 0; j < 27; j++)
      ans[3][i] += dp[i][j];
    ans[3][i] %= MOD;
  }
}
void pre() {
  one();
  two();
  three();
  return;
}
int main() {
  int t, n, k;
  pre();
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k);
    printf("%lld\n", ans[k][n]);
  }
}
