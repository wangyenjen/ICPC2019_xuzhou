#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

typedef long long ll;

int randint(int lb, int ub) {
    return rnd.next(lb, ub);
    //return uniform_int_distribution<int>(lb, ub)(rng);
}

int wrandint(int L,int R,int w) {
    return rnd.wnext(L, R, w);
    /*int ret = randint(L,R);
    if (w>0) {
        while (w--) {
            ret = max(ret,randint(L,R));
        }
    }
    else if (w<0) {
        w = abs(w);
        while (w--) {
            ret = min(ret,randint(L,R));
        }
    }
    return ret;*/
}

void del_init_test() {
    char str[100];
    sprintf(str, "rm inputs/*.txt");
    system(str);
}

int cases = 0;

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

typedef pair<int, int> pii;
#define F first
#define S second
const int N = 200000;

void gen(int w, bool flag = true) {
    open_file();
    int n = randint(N - 5, N);
    vector<int> per;
    for (int i = 1; i <= n; ++i) {
        per.push_back(i);
    }
    shuffle(per.begin(), per.end());
    vector<pii> e;
    for (int i = 2; i <= n; ++i) {
        int p = wrandint(1, i - 1, w);
        e.push_back(make_pair(p, i));
    }
    shuffle(e.begin(), e.end());
    printf("%d\n", n);
    for (pii p:e) {
        if (randint(1, 2) == 1) swap(p.F, p.S);
        if (!flag) printf("%d %d\n", p.F, p.S);
        else printf("%d %d\n", per[p.F - 1], per[p.S - 1]);
    }
}

void gen_bst(bool flag) {
    open_file();
    int n = randint(N - 5, N);
    vector<int> per;
    for (int i = 1; i <= n; ++i) {
        per.push_back(i);
    }
    shuffle(per.begin(), per.end());
    vector<pii> e;
    for (int i = 2; i <= n; ++i) {
        int p = i / 2;
        e.push_back(make_pair(p, i));
    }
    shuffle(e.begin(), e.end());
    printf("%d\n", n);
    for (pii p:e) {
        if (randint(1, 2) == 1) swap(p.F, p.S);
        if (!flag) printf("%d %d\n", p.F, p.S);
        else printf("%d %d\n", per[p.F - 1], per[p.S - 1]);
    }
}

void gen_chain(int n) {
    open_file();
    vector<int> per;
    for (int i = 1; i <= n; ++i) {
        per.push_back(i);
    }
    shuffle(per.begin() + 1, per.end());
    vector<pii> e;
    for (int i = 2; i <= n; ++i) {
        int p = i / 2;
        if (i <= 3) p = 1;
        else p = i - 2;
        e.push_back(make_pair(p, i));
    }
    shuffle(e.begin(), e.end());
    printf("%d\n", n);
    for (pii p:e) {
        if (randint(1, 2) == 1) swap(p.F, p.S);
        printf("%d %d\n", per[p.F - 1], per[p.S - 1]);
    }
}

void gen_chain_per(int cnt) {
    open_file();
    int n = randint(N - 1, N);
    vector<int> per;
    for (int i = 1; i <= n; ++i) {
        per.push_back(i);
    }
    shuffle(per.begin() + cnt, per.end());
    vector<pii> e;
    for (int i = 2; i <= n; ++i) {
        int p = i -1;
        e.push_back(make_pair(p, i));
    }
    shuffle(e.begin(), e.end());
    printf("%d\n", n);
    for (pii p:e) {
        if (randint(1, 2) == 1) swap(p.F, p.S);
        printf("%d %d\n", per[p.F - 1], per[p.S - 1]);
    }
}

int main (int argc, char **argv) {
    del_init_test();
    registerGen(argc, argv, 1);
    gen(0);
    gen(3);
    gen(-4);
    gen(15);
    gen(-14);
    gen(61);
    gen(-61);
    gen(0, false);
    gen_bst(true);
    gen_bst(false);
    gen(205);
    gen(-444);
    gen(777);
    gen_chain(N - 1);
    gen_chain(N);
    gen_chain_per(0);
    gen_chain_per(0);
    gen_chain_per(0);
    gen_chain_per(1);
    gen_chain_per(1);
    check_test();
}

