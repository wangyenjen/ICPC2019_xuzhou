#include "testlib.h"
using namespace std;

const int T = 500000;
const long long C1 = 1000000000000000000ll;
const long long C2 = 2000000000000000000ll;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, T, "T");
    inf.readEoln();
    for (int i = 1; i <= t; ++i) {
        long long l = inf.readLong(1, C1, "l");
        inf.readSpace();
        inf.readLong(l, C1, "r");
        inf.readSpace();
        inf.readLong(0, C2, "w");
        inf.readEoln();
    }
    inf.readEof();
}
