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

