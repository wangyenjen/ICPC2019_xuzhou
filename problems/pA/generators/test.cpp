#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<pii, ll> piii;
const ll C1 = 1000000000000000000ll;
const ll C2 = 2000000000000000000ll;
const int T = 500000;
//0123456789012345678901234567890123456

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

int cases = 0;

void del_init_test() {
    char str[100];
    sprintf(str, "rm inputs/*.txt");
    system(str);
}

void open_file() {
    char str[100];
    sprintf(str, "inputs/%02d.txt", ++cases);
    freopen(str, "w", stdout);
    cerr << "now generating test " << cases << endl;
}

void check_test() {
    for (int i = 1; i <= cases; ++i) {
        char str[100];
        sprintf(str, "./validator < inputs/%02d.txt", i);
        //fprintf(stderr, str);
        cerr << str << endl;
        system(str);
    }
}

void gen_pure_rnd() {
    open_file();
    int t = T;
    printf("%d\n", t);
    while (t--) {
        ll l = rnd.next(1ll, C1);
        ll r = rnd.next(1ll, C1);
        if (l > r) swap(l, r);
        printf("%lld %lld %lld\n", l, r, rnd.next(0ll, C2));
    }
}

vector<piii> all;

void put_test(ll L, ll R) {
    if (L > R || L < 1 || R > C1) return;
    for (ll l = L; l <= L + 8; ++l) {
        for (ll r = R - 8; r <= R; ++r) {
            if (L <= l && l <= r && r <= R) {
                all.push_back({{L, R}, Xor(l, r) + 1});
                all.push_back({{L, R}, Xor(l, r)});
                all.push_back({{L, R}, max(0ll, Xor(l, r) - 1)});
            }
        }
    }
    all.push_back({{L, R}, rnd.next(Xor(L, R) + 1, C2)});
}

void UNI() {
    sort(all.begin(), all.end());
    all.resize(unique(all.begin(), all.end()) - all.begin());
}

void gen_man() {
    ll magic = (1ll << 59);
    for (int i = 0; i <= 70; ++i) {
        for (int j = 0; j <= 70; ++j) {
            put_test(i, j);
            put_test(i, C1 - j);
            put_test(i, magic - j);
            put_test(i, magic + j);
            put_test(C1 - i, C1 - j);
            put_test(magic - i, magic + j);
            put_test(magic + i, magic + j);
            put_test(magic - i, magic - j);
        }
        if (i % 10 == 0) UNI();
    }
    UNI();
    //cerr << "size1 = " << all.size() << endl;
    vector<ll> ls = {1, magic};
    for (ll l: ls) {
        for (ll del = 0; del <= 10; ++del) {
            ll len = l + del;
            int cnt = 50;
            while (cnt--) {
                ll l = rnd.next(1ll, C1 - len + 1);
                put_test(l, l + len - 1);
            }
        }
    }
    UNI();
    //cerr << "size2 = " << all.size() << endl;
    while ( (int)all.size() < T * 4) {
        ll l = rnd.next(1ll, C1);
        ll r = rnd.next(1ll, C1);
        if (l > r) swap(l, r);
        put_test(l, r);
        if (rnd.next(1, 100) == 87) {
            all.push_back({{l, r}, C2});
            all.push_back({{l, r}, 0});
        }
    }
    UNI();
    //cerr << "size3 = " << all.size() << endl;
    while ( (int)all.size() != T * 3 ) {
        ll l = rnd.next(1ll, C1);
        ll r = rnd.next(1ll, C1);
        if (l > r) swap(l, r);
        all.push_back({{l, r}, rnd.next(1ll, C2)});
    }
    shuffle(all.begin(), all.end());
    int left = 0;
    int tot = (int)all.size();
    for (piii p: all) {
        if (left == 0) {
            open_file();
            left = min(T, tot);
            printf("%d\n", left);
        }
        printf("%lld %lld %lld\n", p.first.first, p.first.second, p.second);
        --left;
        --tot;
    }
}

int main(int argc, char **argv) {
    del_init_test();
    registerGen(argc, argv, 1);
    gen_pure_rnd();
    gen_man();
    check_test();
}
