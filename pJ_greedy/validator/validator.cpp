#include "./../../include/testlib.h"
using namespace std;

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    inf.readInt(2, 1000, "N");
    inf.readEoln();
    inf.readEof();
}
