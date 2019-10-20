#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 200000;

int cases = 0;

void del_init_test() {
    char str[100];
    sprintf(str, "rm inputs/*.txt");
    system(str);
}

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
    }
}

void gen_rnd(int w) {
    open_file();
    int n = rnd.wnext(1, N, 1000), q = rnd.wnext(1, N, 1000);
    printf("%d %d\n", n, q);
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", rnd.wnext(1, N, w), " \n"[i == n]);
    }
    while (q--) {
        int t = rnd.next(1, 2);
        printf("%d", t);
        if (t == 1) {
            printf(" %d %d\n", rnd.next(1, n), rnd.next(1, N));
        }
        else {
            int l = rnd.next(1, n), r = rnd.next(1, n);
            if (l > r) swap(l, r);
            printf(" %d %d\n", l, r);
        }
    }
}

#define QUIT if(q==0)return;
#define show(t,l,r) printf("%d %d %d\n", (t), (l), (r)); --q; QUIT

set< pair<int, int> > qs;

void go(int t, int l, int r, int &n, int &q) {
    if (t == 2) {
        if (qs.find({l, r}) != qs.end()) {
            return;
        }
        if (1 <= l && l <= r && r <= n) {
            show(t, l, r);
            qs.insert({l, r});
        }
        else return;
    }
    else if (t == 1) {
        show(t, l, r);
    }
}

#define gogo(t, l, r, n, q) go((t), (l), (r), (n), (q)); QUIT;

vector<int> gett(int n, int c) {
    set<int> st;
    while ( (int)st.size() != c) {
        st.insert(rnd.next(1, n));
    }
    vector<int> v;
    for (int i: st) {
        v.push_back(i);
    }
    shuffle(v.begin(), v.end());
    return v;
}

vector<int> gett2(int n, int c, int k1) {
    set<int> st;
    while ( (int)st.size() != c) {
        st.insert(rnd.next(1, n));
    }
    vector<int> v;
    for (int i: st) {
        v.push_back(i);
    }
    vector<int> v1, v2;
    int start = rnd.next(0, c - k1);
    for (int i = 0; i < c; ++i) {
        if (i < start || i > start + k1 - 1) v2.push_back(v[i]);
        else v1.push_back(v[i]);
    }
    vector<int> ret;
    shuffle(v1.begin(), v1.end());
    shuffle(v2.begin(), v2.end());
    for (int i: v1) ret.push_back(i);
    for (int i: v2) ret.push_back(i);
    return ret;
}


void gen_man1(int w) {
    open_file();
    int n = N, q = N;
    println(n, q);
    vector<int> pos;
    vector<int> all;
    for (int i = 1; i <= n; ++i) {
        if (i <= 18) printf("%d ", (1 << (i - 1)));
        else printf("%d%c", (w == 1 ? N : rnd.next(1, N)), " \n"[i == n]);
        if (i <= 18) {
            pos.push_back(i);
        }
        all.push_back(i);
    }
    bool first = true;
    while (true) {
        qs.clear();
        gogo(2, 1, n, n, q);
        for (int i: pos) {
            for (int j: pos) {
                if (i > j) continue;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        gogo(2, i + di, j + dj, n, q);
                    }
                }
                vector<int> tmp = pos;
                sort(tmp.begin(), tmp.end());
                auto iter1 = lower_bound(tmp.begin(), tmp.end(), i);
                auto iter2 = lower_bound(tmp.begin(), tmp.end(), j);
                int l = 1, r = n;
                if (iter1 != tmp.begin()) l = rnd.next(*prev(iter1) + 1, i);
                if (iter2 != prev(tmp.end())) r = rnd.next(j, *next(iter2) - 1);
                gogo(2, l, r, n, q);
                if (iter1 != tmp.begin()) l = rnd.next(*prev(iter1) + 1, i);
                if (iter2 != prev(tmp.end())) r = rnd.next(j, *next(iter2) - 1);
                gogo(2, l, r, n, q);
            }
        }
        vector<int> newpos = pos;
        if (first) reverse(newpos.begin(), newpos.end());
        else newpos = gett(n, 18);
        for (int i = 0; i < 18; ++i) {
            int val = (w == 1 ? N - rnd.next(1, N / 10) : rnd.next(1, N));
            gogo(1, pos[i], val, n, q);
        }
        for (int i = 0; i < 18; ++i) {
            gogo(1, newpos[i], (1 << i), n, q);
        }
        pos = newpos;
        first = false;
    }
}

void gen_man2(int w) {
    open_file();
    int n = N, q = N;
    println(n, q);
    vector<int> pos;
    vector<int> all;
    for (int i = 1; i <= n; ++i) {
        if (i <= 35) {
            int val;
            if (i == 1) val = 1;
            else val = rnd.next((1 << (i / 2 - 1)), min(n, (1 << ((i / 2))) - 1));
            printf("%d ", val);
        }
        else printf("%d%c", (w == 1 ? N : rnd.next(1, N)), " \n"[i == n]);
        if (i <= 35) {
            pos.push_back(i);
        }
        all.push_back(i);
    }
    bool first = true;
    while (true) {
        qs.clear();
        gogo(2, 1, n, n, q);
        for (int i: pos) {
            for (int j: pos) {
                if (i > j) continue;
                if (i <= pos[0] && pos[0] <= j) ;
                else continue;
                for (int di = 0; di <= 0; ++di) {
                    for (int dj = 0; dj <= 0; ++dj) {
                        if (i + di <= pos[0] && pos[0] <= j + dj) {
                            gogo(2, i + di, j + dj, n, q);
                        }
                    }
                }
                vector<int> tmp = pos;
                sort(tmp.begin(), tmp.end());
                auto iter1 = lower_bound(tmp.begin(), tmp.end(), i);
                auto iter2 = lower_bound(tmp.begin(), tmp.end(), j);
                int l = 1, r = n;
                if (iter1 != tmp.begin()) l = rnd.next(*prev(iter1) + 1, i);
                if (iter2 != prev(tmp.end())) r = rnd.next(j, *next(iter2) - 1);
                gogo(2, l, r, n, q);
            }
        }
        vector<int> newpos = pos;
        newpos = gett2(n, 35, rnd.next(0, 35));
        for (int i = 0; i < 35; ++i) {
            int val = (w == 1 ? N - rnd.next(1, N / 10) : rnd.next(1, N));
            gogo(1, pos[i], val, n, q);
        }
        for (int i = 0; i < 35; ++i) {
            int val = 1;
            if (i)  val = rnd.next((1 << ((i + 1) / 2 - 1)), min(n, (1 << (((i + 1) / 2))) - 1));
            gogo(1, newpos[i], val, n, q);
        }
        pos = newpos;
        first = false;
    }
}

typedef pair<int, int> pii;

int a[N + 6];

void gen_time_max() {
    open_file();
    int n = N, q = N;
    for (int i = 1; i <= n; ++i) {
        a[i] = N;
        if (98765 <= i && i <= 98765 + 17) {
            a[i] = (1 << (i - 98765));
        }
    }
    println(n, q);
    println(a + 1, a + n + 1);
    vector<pii> v;
    for (int i = 1; i <= 300; ++i) {
        for (int j = 1; j <= 300; ++j) {
            v.push_back({i, n - j + 1});
        }
    }
    while ( (int)v.size() != q ) {
        v.push_back({rnd.next(1, 40000), rnd.next(160000, 200000)});
    }
    shuffle(v.begin(), v.end());
    for (pii p: v) {
        println(2, p.first, p.second);
    }
}

void gen_time_max_2() {
    open_file();
    int n = N, q = N;
    for (int i = 1; i <= n; ++i) {
        a[i] = N;
        if (118765 <= i && i <= 118765 + 17) {
            a[i] = (1 << (i - 118765));
        }
    }
    println(n, q);
    println(a + 1, a + n + 1);
    vector<pii> v;
    for (int i = 1; i <= 200; ++i) {
        for (int j = 1; j <= 200; ++j) {
            v.push_back({i, n - j + 1});
        }
    }
    while ( (int)v.size() != q / 2) {
        v.push_back({rnd.next(1, 40000), rnd.next(160000, 200000)});
    }
    shuffle(v.begin(), v.end());
    for (pii p: v) {
        println(2, p.first, p.second);
        println(1, (rnd.next(1, 2) == 1 ? rnd.next(1, 80000) : rnd.next(120000, n)), rnd.next(1, N));
    }
}

void gen_man3(int kw) {
    open_file();
    int n = N, q = N;
    println(n, q);
    for (int i = 1; i <= n; i += kw) {
        int pre = 0;
        vector<int> v;
        bool flag = true;
        for (int j = 1; j <= kw; ++j) {
            if (!flag || pre >= N) {
                v.push_back(N);
            }
            else if (rnd.next(1, (kw - j + 1) * (kw - j + 2)) == 1) {
                //fail
                flag = false;
                if (rnd.next(1, 2) == 1) v.push_back(pre + rnd.next(2, 5));
                else v.push_back(rnd.next(pre + 2, N));
            }
            else {
                int val = rnd.next(1, pre + 1);
                if (rnd.next(1, 2) == 1) val = max(1, 1 + pre - rnd.next(0, 3));
                v.push_back(val);
                pre += val;
            }
        }
        shuffle(v.begin(), v.end());
        for (int k = 0; k < kw; ++k) {
            a[i + k] = v[k];
        }
    }
    println(a + 1, a + n + 1);
    for (int i = 1; i <= q; ++i) {
        if (i <= q / kw) println(2, (i - 1) * kw + 1, i * kw);
        else {
            if (i % 2 == 1) {
                int pos = rnd.next(1, n);
                while (a[pos] == N) {
                    pos = rnd.next(1, n);
                }
                println(1, pos, N);
            }
            else {
                int l = rnd.next(1, n), r = rnd.next(1, n);
                if (l > r) swap(l, r);
                if (rnd.next(1, 2) == 1) println(2, l, r);
                else {
                    int id = rnd.next(1, n / kw);
                    println(2, (id - 1) * kw + 1, id * kw);
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    del_init_test();
    registerGen(argc, argv, 1);
    gen_rnd(0);
    gen_rnd(-5);
    gen_man1(1);
    gen_man1(2);
    gen_time_max();
    gen_time_max_2();
    gen_man2(1);
    gen_man2(2);
    gen_man3(20);
    gen_man3(25);
    check_test();
}
