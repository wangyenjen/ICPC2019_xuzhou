/*
這是一道根號題。

把序列 N^0.5 分快，分別維護每塊到每塊的答案， a_ij 計為 第 i 塊跟第 j 塊的答案。

考慮詢問，詢問可以拆成大塊 vs 大塊，大塊 vs 小塊，小塊 vs 小塊。大塊 vs 小塊、小塊 vs 小塊都是 trivial 。大塊 vs 大塊，需要做的就是問一個 a_ij 的矩形和是多少。這個部份我們開 N^{0.5} 條前綴和陣列維護。

考慮修改，最麻煩的是對於 a_ij ，修改對會動到一個十字狀的值。對於水平的，重新建造那條新的前綴和陣列就好。對於鉛直的，另外維護「鉛直」的前綴和就行了！

複雜度： O(N^1.5)
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100006;
const int K = 336;

int n, q;
int a[N];
int pre_block[N][K];
int pre_col[K][K];
int pre_row[K][K];

void cal(int x, int y) {
    int ans = 0;
    for (int i = K * x; i < min(n + 1, K * (x + 1)); ++i) {
        ans += pre_block[ a[i] ][ y ];
    }
    pre_row[x][y] = pre_row[y][x] = ans;
}

int Pre_row(int i, int L, int R) {
    if (L > R) return 0;
    return pre_row[i][R] - (L ? pre_row[i][L - 1] : 0);
}

int Pre_col(int i, int L, int R) {
    if (L > R) return 0;
    return pre_col[i][R] - (L ? pre_col[i][L - 1] : 0);
}

int Pre_block(int i, int L, int R) {
    if (L > R) return 0;
    return pre_block[i][R] - (L ? pre_block[i][L - 1] : 0);
}

ll query_big(int l, int r, int L, int R) {
    if (l > r || L > R) return 0;
    ll ret = 0;
    for (int i = l; i <= r; ++i) {
        ret += Pre_row(i, L, R);
    }
    for (int i = L; i <= R; ++i) {
        ret += Pre_col(i, l, r);
    }
    return ret;
}

int cnt[N];

int dels[N];

void change(int pos, int val, int del) {
    for (int i = pos / K; i <= n / K; ++i) {
        pre_block[val][i] += del;
    }
    for (int i = 0; i <= n / K; ++i) {
        dels[i] = Pre_block(val, i, i) * del;
        if (i == pos / K) {
            dels[i] += del * (Pre_block(val, i, i) - del);
        }
    }
    int pre = 0;
    for (int i = 0; i <= n / K; ++i) {
        pre += dels[i];
        pre_row[pos / K][i] += pre;
    }
    dels[pos / K] = 0;
    pre = 0;
    for (int i = 0; i <= n / K; ++i) {
        pre += dels[i];
        pre_col[pos / K][i] += pre;
    }
}

int main () {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        pre_block[ a[i] ][ i / K ]++;
    }
    for (int i = 0; i <= n / K; ++i) {
        for (int j = i; j <= n / K; ++j) {
            cal(i, j);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n / K; ++j) {
            pre_block[i][j] += pre_block[i][j - 1];
        }
    }
    for (int i = 0; i <= n / K; ++i) {
        for (int j = 0; j <= n / K; ++j) {
            if (j) pre_row[i][j] += pre_row[i][j - 1];
        }
    }
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int pos, val; scanf("%d%d", &pos, &val);
            --pos;
            if (val == a[pos]) continue;
            change(pos, a[pos], -1);
            a[pos] = val;
            change(pos, a[pos], 1);
        }
        else if (t == 2) {
            int L, R, l, r; scanf("%d%d%d%d", &L, &R, &l, &r);
            --L; --R; --l; --r;
            int bL = L / K, bR = R / K, bl = l / K, br = r / K;
            ll ans = query_big(bL + 1, bR - 1, bl + 1, br - 1);
            vector<int> bLR, blr;
            //big small
            for (int i = L; i / K == bL && i <= R; ++i) {
                ans += Pre_block(a[i], bl + 1, br - 1);
                bLR.push_back(a[i]);
            }
            if (bL != bR) {
                for (int i = R; i / K == bR && i >= L; --i) {
                    ans += Pre_block(a[i], bl + 1, br - 1);
                    bLR.push_back(a[i]);
                }
            }
            for (int i = l; i / K == bl && i <= r; ++i) {
                ans += Pre_block(a[i], bL + 1, bR - 1);
                blr.push_back(a[i]);
            }
            if (bl != br) {
                for (int i = r; i / K == br && i >= l; --i) {
                    ans += Pre_block(a[i], bL + 1, bR - 1);
                    blr.push_back(a[i]);
                }
            }
            //small small
            for (int i: blr) {
                cnt[i]++;
            }
            for (int j: bLR) {
                ans += cnt[j];
            }
            for (int i: blr) {
                cnt[i] = 0;
            }
            printf("%lld\n", ans);
        }
    }
}

