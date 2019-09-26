#include "testlib.h"
using namespace std;

const int N = 100000;
const int Q = 100000;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N, "n");
    inf.readSpace();
    int q = inf.readInt(1, Q, "q");
    inf.readEoln();
    inf.readInts(n, 1, N, "a", 1);
    inf.readEoln();
    for (int i = 1; i <= q; ++i) {
        int t = inf.readInt(1, 2, "t");
        if (t == 1) {
            inf.readSpace();
            inf.readInt(1, n, "pos");
            inf.readSpace();
            inf.readInt(1, N, "val");
            inf.readEoln();
        }
        else {
            inf.readSpace();
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            inf.readInt(l, n, "r");
            inf.readSpace();
            int L = inf.readInt(1, n, "L");
            inf.readSpace();
            inf.readInt(L, n, "R");
            inf.readEoln();
        }
    }
    inf.readEof();
}
