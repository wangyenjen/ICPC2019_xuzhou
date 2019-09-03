#include <testlib.h>

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1'000'000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1'000'000, "m");
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        inf.readInt(1, n, "a_i");
        inf.readSpace();
        inf.readInt(1, n, "b_i");
        inf.readEoln();
    }
    inf.readEof();
}
