#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

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
        cerr << str << endl;
        system(str);
    }
}

void gen_rnd() {
    open_file();
    int n = N, q = N;
    printf("%d %d\n", n, q);
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", rnd.next(1, N), " \n"[i == n]);
    }
    while (q--) {
        int t = rnd.next(1, 2);
        printf("%d", t);
        if (t == 1) {
            printf(" %d %d\n", rnd.next(1, n), rnd.next(1, N));
        }
        else {
            int l = rnd.next(1, n), r = rnd.next(1, n);
            int L = rnd.next(1, n), R = rnd.next(1, n);
            if (l > r) swap(l, r);
            if (L > R) swap(L, R);
            printf(" %d %d %d %d\n", L, R, l, r);
        }
    }
}

void gen_rnd2(int w1, int w2) {
    open_file();
    int n = rnd.wnext(1, N, 1000), q = rnd.wnext(1, N, 1000);
    printf("%d %d\n", n, q);
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", rnd.wnext(1, N, w1), " \n"[i == n]);
    }
    while (q--) {
        int t = rnd.next(1, 2);
        printf("%d", t);
        if (t == 1) {
            printf(" %d %d\n", rnd.next(1, n), rnd.wnext(1, N, w2));
        }
        else {
            int l = rnd.wnext(1, n, -2), r = rnd.wnext(1, n, 2);
            int L = rnd.wnext(1, n, -2), R = rnd.wnext(1, n, 2);
            if (l > r) swap(l, r);
            if (L > R) swap(L, R);
            printf(" %d %d %d %d\n", L, R, l, r);
        }
    }
}

void gen_man1(int c, int type, int w1, int w2) {
    open_file();
    vector<int> v;
    for (int i = 0; i < c; ++i) {
        v.push_back(rnd.next(1, N));
    }
    int n = rnd.wnext(1, N, 4000), q = rnd.wnext(1, N, 4000);
    if (type >= 1) n = q = N;
    printf("%d %d\n", n, q);
    if (type <= 1) {
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", (type == 1 ? N : rnd.wnext(1, N, w2)), " \n"[i == n]);
        }
    }
    else {
        vector<int> vv;
        for (int i = 1; i <= n; ++i) {
            vv.push_back(i);
        }
        shuffle(vv.begin(), vv.end());
        for (int i = 1; i <= n; ++i) {
            printf("%d%c", vv[i - 1], " \n"[i == n]);
        }
        printf("2 1 %d %d %d\n", n / 2, n / 2 + 1, n);
        --q;
    }
    printf("2 1 %d 1 %d\n", n, n);
    --q;
    while (q--) {
        int t = rnd.next(1, 2);
        printf("%d", t);
        if (t == 1) {
            printf(" %d %d\n", rnd.next(1, n), v[rnd.wnext(0, c - 1, w2)]);
        }
        else {
            int l = rnd.wnext(1, n, -50), r = rnd.wnext(1, n, 50);
            int L = rnd.wnext(1, n, -50), R = rnd.wnext(1, n, 50);
            if (l > r) swap(l, r);
            if (L > R) swap(L, R);
            printf(" %d %d %d %d\n", L, R, l, r);
        }
    }
}

int main(int argc, char **argv) {
    del_init_test();
    registerGen(argc, argv, 1);
    gen_rnd();
    gen_rnd2(50, 80);
    gen_rnd2(-95, 123);
    gen_man1(100, 1, 0, 0);
    gen_man1(1000, 1, 0, 50);
    gen_man1(10, 0, 10, -6);
    gen_man1(800, 0, 50, -50);
    gen_man1(1000, 2, 50, -10);
    gen_rnd();
    check_test();
}
