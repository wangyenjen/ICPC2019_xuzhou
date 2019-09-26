#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

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

typedef long long ll;

//mt19937 rng(880301);
int randint(int lb, int ub) {
    return rnd.next(lb, ub);
    //return uniform_int_distribution<int>(lb, ub)(rng);
}

int wrandint(int L, int R, int w) {
    return rnd.wnext(L, R, w);
    /*int ret = randint(L,R);
    if (w>0) {
        while (w--) {
            ret = max(ret,randint(L,R));
        }
    }
    else if (w<0) {
        w = abs(w);
        while (w--) {
            ret = min(ret,randint(L,R));
        }
    }
    return ret;*/
}

ll randll() {
    ll x = randint(0, 2147483647);
    return ((x << 30) ^ (randint(0, 2147483647)));
}

ll randll(ll l, ll r) {
    return rnd.next(l, r);
    //return randll() % (r - l + 1) + l;
}

typedef vector<int> vint;

const int N = 100000;
const int SIGMA = 1000000000;

vector<int> gen_str(int sz) {
    vector<int> ret;
    while (sz--) {
        ret.push_back((randint(1, 1 + SIGMA - 1)));
    }
    return ret;
}

vint s[N + 6];

vint tar, tar2;
int ppos;

vint ggen_str(int len) {
    if (randint(1, 2) == 1) swap(tar, tar2);
    int p = randint(1, 100);
    vint ret;
    if (p <= 15) {
        ret = gen_str(len);
    }
    else if (p <= 60) {
        ret = tar;
        ret[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
    }
    else if (p <= 90) {
        ret = tar;
        ret[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
        if (randint(1, 2) <= 1) ret[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
        else ret[ppos] = randint(1, 1 + SIGMA - 1);
    }
    else {
        ret = tar;
        ret[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
        ret[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
        if (randint(1, 2) <= 1) ret[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
        else ret[ppos] = randint(1, 1 + SIGMA - 1);
    }
    return ret;
}

void show(vint v) {
    cout << (int)v.size();
    for (int i: v) cout << ' ' << i;
    cout << '\n';
}

vint qs[N + 6];

void gen(int len) {
    open_file();
    int n = N / len;
    cout << n << endl;
    set<vint> st;
    tar = gen_str(len);
    tar2 = gen_str(len);
    vector<int> idx;
    ppos = randint(0, len - 1);
    for (int i = 1; i <= n; ++i) {
        vint t = ggen_str(len);
        while (st.find(t) != st.end()) {
            t = gen_str(len);
        }
        if (i == 1) t = tar;
        st.insert(t);
        s[i] = t;
        idx.push_back(i);
        //cout << t << endl;
    }
    shuffle(idx.begin(), idx.end());
    for (int i: idx) {
        show(s[i]);
        //cout << s[i] << endl;
    }
    int q = N / len;
    cout << q << endl;
    st.clear();
    //set<vint> st;
    while ((int)st.size() != q) {
        int ret = randint(1, 100);
        vint qq;
        if (ret <= 5) {
            qq = gen_str(len);
            //cout << gen_str(len) << endl;
        }
        else if (ret <= 25) {
            qq = s[ randint(1, n) ];
            //cout << s[ randint(1, n) ] << endl;
        }
        else if (ret <= 60) {
            vint t = s[ randint(1, n) ];
            if (randint(1, 10) != 1) t[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
            else t[ppos] = randint(1, 1 + SIGMA - 1);
            qq = t;
            //cout << t << endl;
        }
        else if (ret <= 85) {
            vint t = s[ randint(1, n) ];
            t[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
            //t[ randint(0, len - 1) ] = randint('a', 'a' + SIGMA - 1);
            if (randint(1, 2) <= 1) t[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
            else t[ppos] = randint(1, 1 + SIGMA - 1);
            qq = t;
            //cout << t << endl;
        }
        else {
            vint t = s[ randint(1, n) ];
            t[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
            t[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
            //t[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
            if (randint(1, 2) <= 1) t[ randint(0, len - 1) ] = randint(1, 1 + SIGMA - 1);
            else t[ppos] = randint(1, 1 + SIGMA - 1);
            //cout << t << endl;
            qq = t;
        }
        st.insert(qq);
    }
    shuffle(idx.begin(), idx.end());
    int id = 1;
    for (vint ss: st) {
        qs[id] = ss;
        ++id;
    }
    for (int id: idx) {
        show(qs[id]);
        //cout << qs[id] << endl;
    }
}

void gen_full(int no) {
    open_file();
    int n = 1, q = 1;
    cout << n << endl;
    vint s = gen_str(N);
    show(s);
    //cout << s << endl;
    set<int> pos;
    while ( (int)pos.size() != no) {
        pos.insert(randint(0, N - 1));
    }
    for (int i: pos) {
        int c = randint(1, 1 + SIGMA - 1);
        while (c == s[i]) {
            c = randint(1, 1 + SIGMA - 1);
        }
        s[i] = c;
    }
    cout << q << endl;
    show(s);
    //cout << s << endl;
}

int ppow(int a, int n) {
    int ret = 1;
    while (n--) ret *= a;
    return ret;
}

vector<string> all;

string dfs_str;

void gen_man1() {
    open_file();
    int len = N / 12;
    int n = 12, q = 12;
    cout << n << endl;
    vector<int> idx;
    for (int i = 1; i <= n; ++i) {
        s[i] = gen_str(len);
        show(s[i]);
        //cout << s[i] << endl;
        idx.push_back(i);
    }
    shuffle(idx.begin(), idx.end());
    vector<vint> qs;
    for (int no = 0; no <= 3; ++no) {
        for (int mask = 0; mask < 4; ++mask) {
            vint tar = s[ idx[(int)qs.size()] ];
            if (no == 0) {
                qs.push_back(tar);
                break;
            }
            set<int> pos;
            if (no == 1) {
                if (mask == 0) {
                    pos.insert(randint(1, len - 2));
                }
                else if (mask == 1) {
                    pos.insert(0);
                }
                else if (mask == 2) {
                    pos.insert(len - 1);
                }
                else break;
            } 
            else {
                if (mask == 1 || mask == 3) {
                    pos.insert(0);
                }
                if (mask == 2 || mask == 3) {
                    pos.insert(len - 1);
                }
            }
            while((int)pos.size() != no) {
                pos.insert(randint(1, len - 2));
            }
            for (int i: pos) {
                int c = randint(1, 1 + SIGMA - 1);
                while (c == tar[i]) {
                    c = randint(1, 1 + SIGMA - 1);
                }
                tar[i] = c;
            }
            qs.push_back(tar);
        }
    }
    shuffle(qs.begin(), qs.end());
    cout << q << endl;
    for (vint s: qs) {
        show(s);
        //cout << s << endl;
    }
}

void do_man2() {
    vector<vint> v;
    int tot_sz = 0;
    while ( tot_sz + 15 <= N ) {
        int type = randint(1, 5);
        int len = -1;
        if (type == 1) {
            len = randint(500 - 1, 500 + 1);
        }
        else {
            len = randint(15, 25);
        }
        if (tot_sz + len > N) continue;
        v.push_back( gen_str(len) );
        tot_sz += len;
    }
    cout << (int)v.size() << endl;
    shuffle(v.begin(), v.end());
    for (vint i: v) {
        show(i);
        //cout << i << endl;
    }
}

void gen_man2() {
    open_file();
    do_man2();
    do_man2();
}

int main(int argc, char **argv) {
    del_init_test();
    registerGen(argc, argv, 1);
    for (int i = 1; i <= 5; ++i) {
        gen(i);
    }
    gen(20);
    gen(30);
    gen(40);
    gen(50);
    gen(60);
    gen(70);
    gen(80);
    gen(90);
    gen(100);
    gen(200);
    gen(300);
    gen(400);
    gen(500);
    gen(600);
    gen(700);
    gen(800);
    gen(10000);
    gen(50000);
    gen_full(0);
    gen_full(1);
    gen_full(2);
    gen_full(3);
    gen_man1();
    gen_man2();
    check_test();
}
