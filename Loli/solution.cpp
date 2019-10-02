/*
可以發現，如果 x % 4 == 0 ，那麼 0 ^ 1 ^ ..... ^ x = 0 （^ 是bitwise xor）。

有了這個性質之後，應該不難發現，在左界是 [L, L + 9], 右界是 [R - 9, R] 中，一定會有一個區間，使得整個區間的 xor 和是零。

因此，應該不難發現，只需要檢查那些區間即可！
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll pre_xor(ll x) {
    if (x % 4 == 0) return x;
    else if (x % 4 == 1) return x ^ (x - 1);
    else if (x % 4 == 2) return x ^ (x - 1) ^ (x - 2);
    else if (x % 4 == 3) return x ^ (x - 1) ^ (x - 2) ^ (x - 3);
    assert(0);
}

ll Xor(ll a, ll b) {
    return pre_xor(a - 1) ^ pre_xor(b);
}

int main () {
    int T; scanf("%d", &T);
    while (T--) {
        ll L, R, c; scanf("%lld%lld%lld", &L, &R, &c);
        ll ans = -1;
        for (ll l = L; l <= L + 8; ++l) {
            for (ll r = R; r >= R - 8; --r) {
                if (L <= l && l <= r && r <= R) {
                    if (Xor(l, r) <= c) {
                        ans = max(ans, r - l + 1);
                    }
                }
            }
        }
        printf("%lld\n", ans);
    }
}

