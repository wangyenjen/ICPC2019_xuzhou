#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 200000;

struct DJS {
    int p[N + 1];
    void init() {
        for (int i = 0; i <= N; ++i) {
            p[i] = i;
        }
    }
    int Find(int x) {
        return p[x] == x ? x : p[x] = Find(p[x]);
    }
    void Union(int x, int y) {
        p[ Find(x) ] = Find(y);
    }
} djs;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N);
    inf.readEoln();
    djs.init();
    for (int i = 1; i < n; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();
        djs.Union(x, y);
    }
    for (int i = 1; i <= n; ++i) {
        ensuref(djs.Find(1) == djs.Find(i), "not a tree!!!!!!");
    }
    inf.readEof();
}
