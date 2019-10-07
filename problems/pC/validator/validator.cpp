#include "./../../include/testlib.h"
#include <bits/stdc++.h>
using namespace std;

#define MAX 100090

struct djs{
    int x[MAX];
    void init(){ for(int i = 0; i < MAX; i ++) x[i] = i; }
    int Find(int now){ return x[now] == now ? now : x[now] = Find(x[now]); }
    void Union(int a , int b){ x[Find(a)] = Find(b); }
    int operator[](int now){ return Find(now); }
} ds;


int main(int argc, char **argv) {
    registerValidation(argc, argv);

    const int maxn = 100000;

    int n = inf.readInt(1, maxn, "n");
    inf.readSpace();
    int m = inf.readInt(1, maxn, "n");
    inf.readEoln();

    ds.init();
    for(int i = 2; i <= n; i ++){
        int v1 = inf.readInt(1, n, "e_1"); inf.readSpace();
        int v2 = inf.readInt(1, n, "e_2"); inf.readSpace();
        int v3 = inf.readInt(1, maxn, "e_c"); inf.readEoln();
        ds.Union(v1 , v2);
    }
    for(int i = 1; i <= n; i ++) assert(ds[i] == ds[1]);
    for(int i = 1; i <= m; i ++){
        int v1 = inf.readInt(1, n, "q_1"); inf.readSpace();
        int v2 = inf.readInt(1, n, "q_2"); inf.readEoln();
    }

    inf.readEof();
}
