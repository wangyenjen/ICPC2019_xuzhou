#include "testlib.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

const int N = 200000;
const int INF = 1000000;
const int MXN = (int)2e5 + 7;


pair<int, int> pt[MXN];
int n, k;
bool f = false;
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
int in[2*INF + 7];
void gen_full(int k_top) {
    open_file();
    n = N, k = rnd.next(1, k_top);
    printf("%d %d\n", n, k);

    for (int i = 0; i < n; i++) {
        int x = rnd.next(-INF, INF);
        while (in[x + INF] == cases) x = rnd.next(-INF, INF);
        in[x + INF] = cases;
        int y = rnd.next(1, INF);
        pt[i] = {x, y};
    }
    sort(pt, pt + n);
    for (int i = 0; i < n; i++)
        printf("%d %d\n", pt[i].first, pt[i].second);
}
void gen_rnd(int n_top, int k_top) {
    open_file();
    n = rnd.next(1, n_top), k = rnd.next(1, k_top);
    printf("%d %d\n", n, k);

    for (int i = 0; i < n; i++) {
        int x = rnd.next(-INF, INF);
        while (in[x + INF] == cases) x = rnd.next(-INF, INF);
        in[x + INF] = cases;
        int y = rnd.next(1, INF);
        pt[i] = {x, y};
    }
    sort(pt, pt + n);
    for (int i = 0; i < n; i++)
        printf("%d %d\n", pt[i].first, pt[i].second);
}
int buf[N + 7], realv[N + 7];
void gen_mono(int n_top, int k_top, bool inc) {
    open_file();
    n = rnd.next(1, n_top), k = rnd.next(1, k_top);
    if (f) n = n_top, f = false;
    printf("%d %d\n", n, k);

    for (int i = 1; i <= n; i++) {
        int x = rnd.next(-INF, INF);
        while (in[x + INF] == cases) x = rnd.next(-INF, INF);
        in[x + INF] = cases;
        pt[i].first = x;
    }
	for (int i = 1; i <= n; i++) {
		int y = rnd.next(1, INF);
		buf[i] = y;
	}

    sort(pt + 1, pt + n + 1);
	if (inc) sort(buf + 1, buf + n + 1);
	else sort(buf + 1, buf + n + 1, greater<int>());

    for (int i = 1; i <= n; i++) {
        pt[i].second = buf[i];
        printf("%d %d\n", pt[i].first, pt[i].second);
    }
}
void gen_sp(int n_top, int k_top, int y_num) {
	open_file();
	n = rnd.next(1, n_top), k = rnd.next(1, k_top);
    if (f) n = n_top, f = false;
	printf("%d %d\n", n, k);
	for (int i = 1; i <= y_num; i++) {
		int y = rnd.next(1, INF);
		while (in[y + INF] == -cases) y = rnd.next(1, INF);
		in[y + INF] = -cases;
		buf[i] = y;
	}

	for (int i = 1; i <= n; i++) {
		int x = rnd.next(-INF, INF);
		while (in[x + INF] == cases) x = rnd.next(-INF, INF);
		in[x + INF] = cases;
		pt[i].first = x;
		pt[i].second = buf[ rnd.next(1, y_num) ];
	}
	sort(pt + 1, pt + n + 1);

	for (int i = 1; i <= n; i++)
		printf("%d %d\n", pt[i].first, pt[i].second);
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
	gen_rnd(1000, 10000);
	gen_rnd(1000, 10000);		
    gen_rnd(1000, 10000);
	gen_rnd(1000, 1000);
	gen_rnd(1000, 10000);
	gen_rnd(1000, 10000);
	gen_rnd(1000, 10000);

    gen_full(1000000);
    gen_full(100000);
    gen_full(1000);
    gen_full(100);
	gen_full(10);

    gen_rnd(200000, 10000);
    gen_rnd(200000, 1000);
    gen_rnd(200000, 500);
    gen_rnd(200000, 100);
    gen_rnd(200000, 10);

    gen_rnd(100000, 10000);
    gen_rnd(100000, 1000);
    gen_rnd(100000, 500);
    gen_rnd(100000, 100);
    gen_rnd(100000, 10);

    gen_rnd(50000, 10000);
    gen_rnd(50000, 1000);
    gen_rnd(50000, 500);
    gen_rnd(50000, 100);
    gen_rnd(50000, 10); 
    f = true;
	gen_mono(200000, 1000000, true);
	gen_mono(200000, 100000, true);
	gen_mono(200000, 10000, true);
	gen_mono(200000, 1000, true);
	gen_mono(200000, 100, true);
    f = true;
	gen_mono(200000, 1000000, false);
	gen_mono(200000, 100000, false);
	gen_mono(200000, 10000, false);
	gen_mono(200000, 1000, false);
	gen_mono(200000, 100, false);
    f = true;
	gen_sp(200000, 5000, 1000);
	gen_sp(200000, 1000, 1000);
	gen_sp(200000, 500, 1000);
	gen_sp(200000, 100, 1000);
	gen_sp(200000, 10, 1000);
    f = true;
	gen_sp(100000, 5000, 100);
	gen_sp(100000, 1000, 100);
	gen_sp(100000, 500, 100);
	gen_sp(100000, 100, 100);
	gen_sp(100000, 10, 100);
    check_test();
}
