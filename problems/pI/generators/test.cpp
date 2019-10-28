#include "testlib.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 300000;
const int INF = 1000000000;
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
		sprintf(str, "./solution < inputs/%02d.txt > outputs/%02d.txt", i, i);
		cerr << str << endl;
		system(str);
    }
}
void gen_full() {
    open_file();
    int n = N;
    printf("%d\n", n);
	for (int i = 1; i <= n; i++) {
		int x = rnd.next(1, INF);
		int y = rnd.next(1, INF);
		printf("%d %d\n", x, y);
	}
}
void gen_rnd(int n_top, int v_top) {
    open_file();
    int n = rnd.next(1, n_top);
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) {
        int x = rnd.next(1, v_top);
        int y = rnd.next(1, v_top);
        printf("%d %d\n", x, y);
    }
}
int a[N + 7], b[N + 7];
int buf[2*N + 7];
void gen_min() {
    open_file();
    int n = N;
    printf("%d\n", n);
    for (int i = 1; i <= 2*n; i++) {
        buf[i] = rnd.next(1, INF);
    }
    sort(buf + 1, buf + 2*n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = buf[i];
        b[i] = buf[i + n];
    }
    shuffle(a + 1, a + n + 1);
    shuffle(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", a[i], b[i]);
    }
}
void gen_max() {
    open_file();
    int n = N;
    printf("%d\n", n);
    for (int i = 1; i <= 2*n; i++) {
        buf[i] = rnd.next(1, INF);
    }
    sort(buf + 1, buf + 2*n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = buf[i + n];
        b[i] = buf[i];
    }
    shuffle(a + 1, a + n + 1);
    shuffle(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", a[i], b[i]);
    }
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    gen_full();
    gen_full();
    gen_full();
    gen_full();
    gen_full();

    gen_rnd(100000, 10000000);
    gen_rnd(100000, 1000000);
    gen_rnd(100000, 100000);
    gen_rnd(100000, 10000);
    gen_rnd(100000, 1000);
    gen_rnd(200000, 10000000);
    gen_rnd(200000, 1000000);
    gen_rnd(200000, 100000);
    gen_rnd(200000, 10000);
    gen_rnd(200000, 1000);
    gen_rnd(10000, 1000);
    gen_rnd(10000, 10000);
    gen_rnd(10000, 100000);
    gen_rnd(10000, 1000000);
    gen_rnd(10000, 10000000);
    gen_rnd(1000, 1000);
    gen_rnd(1000, 10000);
    gen_rnd(1000, 100000);
    gen_rnd(1000, 1000000);
    gen_rnd(1000, 10000000);
    gen_rnd(1000, 100000000);
    gen_rnd(1000, 1000000000);
    gen_rnd(100, 1000000000);
    gen_rnd(100, 1000000000);

    gen_min();
    gen_min();
    gen_min();
    gen_max();
    gen_max();
    gen_max();
    check_test();
}
