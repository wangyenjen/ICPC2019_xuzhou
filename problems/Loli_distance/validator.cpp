#include "testlib.h"
using namespace std;

const int N = 100000;
const int Q = 100000;
const int C = 1000000000;

set<vector<int> > st;

int Check() {
    int sz = inf.readInt(1, N, "sz");
    vector<int> v;
    while (sz--) {
        inf.readSpace();
        v.push_back(inf.readInt(1, C, "val"));
    }
    ensuref(st.find(v) == st.end(), "repeat!!!");
    st.insert(v);
    inf.readEoln();
    return sz;
}

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N, "n");
    inf.readEoln();
    int tot = 0;
    for (int i = 1; i <= n; ++i) {
        tot += Check();
    }
    ensuref(tot <= N, "sigma too big QQQ");
    st.clear();
    int q = inf.readInt(1, N, "q");
    inf.readEoln();
    tot = 0;
    for (int i = 1; i <= q; ++i) {
        tot += Check();
    }
    ensuref(tot <= N, "sigma too big QQQ");
    inf.readEof();
}
