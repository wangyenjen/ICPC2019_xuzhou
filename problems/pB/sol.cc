// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_LOG_BK = 10;
const int MAX_BK = 316 + 7;
const int MAX_N = 100000 + 7;

int a[MAX_N];
int belong[MAX_N];
int bk_sz[MAX_BK];
int bk_st[MAX_BK];
int bk_ed[MAX_BK];
int my_log2[MAX_N];
bitset<MAX_N> bk_xor[MAX_BK];
bitset<MAX_N> bk_or[MAX_BK][MAX_LOG_BK];

void query_or(int l, int r, bitset<MAX_N> &ans) {
  if (belong[l] == belong[r]) {
    for (int i = l; i <= r; i++) {
      ans.set(a[i] - 1);
    }
  }
  else {
    while (belong[l - 1] == belong[l]) {
      ans.set(a[l++] - 1);
    }
    while (belong[r + 1] == belong[r]) {
      ans.set(a[r--] - 1);
    }
    
    if (belong[l] > belong[r]) {
      return;
    }

    int k = my_log2[belong[r] - belong[l] + 1];
    ans |= bk_or[belong[l]][k] | bk_or[belong[r] - (1 << k) + 1][k];
  }
}

void query_xor(int l, int r, bitset<MAX_N> &ans) {
  if (belong[l] == belong[r]) {
    for (int i = l; i <= r; i++) {
      if (ans.test(a[i] - 1)) {
        ans.reset(a[i] - 1);
      } else {
        ans.set(a[i] - 1);
      }
    }
  }
  else {
    while (belong[l - 1] == belong[l]) {
      if (ans.test(a[l] - 1)) {
        ans.reset(a[l++] - 1);
      } else {
        ans.set(a[l++] - 1);
      }
    }
    while (belong[r + 1] == belong[r]) {
      if (ans.test(a[r] - 1)) {
        ans.reset(a[r--] - 1);
      } else {
        ans.set(a[r--] - 1);
      }
    }
    
    if (belong[l] > belong[r]) {
      return;
    }

    ans ^= bk_xor[belong[l] - 1] ^ bk_xor[belong[r]];
  }
}

int main() {
  my_log2[0] = -1;
  for (int i = 1; i < MAX_N; i++) {
    my_log2[i] = my_log2[i >> 1] + 1;
  }

  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);

  int bk_id = 0;
  int bk = (int)sqrt(n + 0.5) << 2;
  
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);

    if (bk_id == 0 || bk_sz[bk_id] == bk) {
      bk_id++;
      bk_st[bk_id] = i;
    }
    
    belong[i] = bk_id;
    bk_sz[bk_id]++;
    bk_ed[bk_id] = i;
  }

  for (int i = 1; i <= bk_id; i++) {
    for (int j = bk_st[i]; j <= bk_ed[i]; j++) {
      if (bk_xor[i].test(a[j] - 1)) {
        bk_xor[i].reset(a[j] - 1);
      } else {
        bk_xor[i].set(a[j] - 1);
      }
      bk_or[i][0].set(a[j] - 1);
    }
  }

  for (int j = 1; (1 << j) <= bk_id; j++) {
    for (int i = 1; i + (1 << j) - 1 <= bk_id; i++)
      bk_or[i][j] = bk_or[i][j - 1] | bk_or[i + (1 << (j - 1))][j - 1];
  }

  for (int i = 2; i <= bk_id; i++) 
    bk_xor[i] ^= bk_xor[i - 1];

  bitset<MAX_N> ans_or;
  bitset<MAX_N> ans_xor;
  for (int qq = 0; qq < q; qq++) {
    int k;
    scanf("%d", &k);
    
    ans_or.reset();
    ans_xor.reset();

    map<int, int> tag;
    for (int i = 0; i < k; i++) {
      int l, r;
      scanf("%d%d", &l, &r);

      tag[l]++;
      tag[r + 1]--;
    }

    int cnt = 0, pre = -1;
    for (auto it : tag) {
      cnt += it.second;
      if (cnt == 0) {
        query_or(pre, it.first - 1, ans_or);
        query_xor(pre, it.first - 1, ans_xor);
        pre = -1;
      } else if (pre == -1) {
        pre = it.first;
      }
    }

    int ans = ans_or.count() - ans_xor.count();
    printf("%d\n", ans);
  }

  return 0;
}

