#include "testlib.h"
using namespace std;

const int N = 200000;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N, "n");
    inf.readSpace();
    int q = inf.readInt(1, N, "q");
    inf.readEoln();
    inf.readInts(n, 1, N, "a", 1);
    inf.readEoln();
    for (int i = 1; i <= q; ++i) {
        int t = inf.readInt(1, 2, "t");
        inf.readSpace();
        if (t == 2) {
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            inf.readInt(l, n, "r");
            inf.readEoln();
        }
        else {
            inf.readInt(1, n, "x");
            inf.readSpace();
            inf.readInt(1, N, "y");
            inf.readEoln();
        }
    }
    inf.readEof();
}
