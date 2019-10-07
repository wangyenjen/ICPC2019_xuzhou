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
const long long INFF = (long long)2e18;
const int MXN = (int)2e5 + 7;


struct Seg {
#define ls p<<1
#define rs p<<1|1
    int ll[MXN<<2], rr[MXN<<2];
    vector<pair<long long, long long>> stk[MXN<<2];
    void bd(int l, int r, int p = 1) {
        ll[p] = l, rr[p] = r; stk[p].clear();
        if (l == r) return ;
        int mid = (l + r) >> 1;
        bd(l, mid, ls);
        bd(mid+1, r, rs);
    }
    long long qy(int pos, int x, int p = 1) {
        long long res = INFF;
        if (!stk[p].empty()) res = min(res, stk[p].back().first + stk[p].back().second*x);
        int mid = (ll[p] + rr[p]) >> 1;
        if (ll[p] == rr[p]) return res;
        else if (pos <= mid) return min(res, qy(pos, x, ls));
        else return min(res, qy(pos, x, rs));
    }
    void add(int l, int r, pair<long long, long long> val, int p = 1) {
        if (ll[p] > r || l > rr[p]) return ;
        if (l <= ll[p] && rr[p] <= r) {
            stk[p].push_back(val);
            return ;
        }
        add(l, r, val, ls);
        add(l, r, val, rs);
    }
    void del(int l, int r, int p = 1) {
        if (ll[p] > r || l > rr[p]) return ;
        if (l <= ll[p] && rr[p] <= r) {
            stk[p].pop_back();
            return ;
        }
        del(l, r, ls);
        del(l, r, rs);
    }
} sg;

pair<int, int> pt[MXN];
int n, k;
long long dp[MXN];
int pos[1000007], lb[1000007], rb[1000007];
vector<int> segy;
deque<pair<long long, long long>> dq[MXN];

bool cmp(pair<long long, long long> p1, pair<long long, long long> p2, long long x) {
    long long v1 = p1.first + p1.second*x;
    long long v2 = p2.first + p2.second*x;
    return v1 >= v2;
}
bool ins(pair<long long, long long> p1, pair<long long, long long> p2, pair<long long, long long> p3) {
    // return (p2.F - p1.F) / (p1.S - p2.S) < (p3.F - p1.F) / (p1.S - p3.S);
    return (p2.first - p1.first) * (p1.second - p3.second) < (p3.first - p1.first) * (p1.second - p2.second);
}
void merge(int y, int u) {
    if (dq[pos[u]].size() < dq[pos[y]].size()) {
        for (auto it = dq[pos[u]].begin(); it != dq[pos[u]].end(); it++) {
            long long val, dlt; tie(val, dlt) = *it;
            while ((int)dq[pos[y]].size() >= 2) {
                auto itr = --dq[pos[y]].end();
                auto itl = itr; itl--;
                if (!ins(*itl, *itr, {val, dlt})) {
                    dq[pos[y]].pop_back();
                } else {
                    break ; 
                }
            }
            dq[pos[y]].push_back({val, dlt});
        }
    } else {
        swap(pos[u], pos[y]);
        int num = 0;
        while (num < 2 && !dq[pos[y]].empty()) {
            auto it = dq[pos[y]].begin();
            while ((int)dq[pos[u]].size() >= 2) {
                auto itr = --dq[pos[u]].end();
                auto itl = itr; itl--;
                if (!ins(*itl, *itr, *it)) {
                    dq[pos[u]].pop_back();
                    if (num) num--;
                } else {
                    break ;
                }
            }
            dq[pos[u]].push_back(*it);
            dq[pos[y]].pop_front();
            num++;
        }
        int sz = (int)dq[pos[u]].size();
        for (int i = sz - 1; i >= 0; i--) {
            dq[pos[y]].push_front(dq[pos[u]][i]);
        }
    }
    dq[pos[u]].clear();
}
void update_convexhull(int id) {
    long long x, y; tie(x, y) = pt[id];
    vector<int> buf; 
    while (!segy.empty()) {
        int h = segy.back();
        if (h > y) break ;
        segy.pop_back();
        if (h != y) buf.push_back(h);
        sg.del(lb[h], rb[h]); rb[h] = -1;

        int p = pos[h];
        while ((int)dq[p].size() >= 2) {
            auto ll = dq[p].begin();
            auto rr = ll; rr++;
            if (cmp(*ll, *rr, y)) { 
                dq[p].pop_front();
            } else {
                break ;
            }
        }
    }
    segy.push_back(y);
    while (!buf.empty()) {
        int h = buf.back(); buf.pop_back();
        merge(y, h);
    }
    while ((int)dq[pos[y]].size() >= 2) {
        auto rr = --dq[pos[y]].end();
        auto ll = rr; ll--;
        if (!ins(*ll, *rr, {dp[id-1], k-x})) {
            dq[pos[y]].pop_back();
        } else {
            break ;
        }
    }
    dq[pos[y]].push_back({dp[id-1], k-x});
    while ((int)dq[pos[y]].size() >= 2) {
        auto ll = dq[pos[y]].begin();
        auto rr = ll; rr++;
        if (cmp(*ll, *rr, y)) {
            dq[pos[y]].pop_front();
        } else {
            break ;
        }
    }
}
void find_min(int id) {
    long long x, y; tie(x, y) = pt[id];

    int ll = id, rr = n, ok = -1;
    long long val, dlt; tie(val, dlt) = *dq[pos[y]].begin();
    while (ll <= rr) {
        int mid = (ll + rr) >> 1;
        long long v = val + dlt*y + y*pt[mid].first;
        long long res = sg.qy(mid, pt[mid].first);
        if (v < res) {
            rr = mid - 1;
            ok = mid;
        } else {
            ll = mid + 1;
        }
    }
    if (ok != -1) {
        lb[y] = ok; rb[y] = n;
        sg.add(lb[y], rb[y], {val+dlt*y, y});
    }
    dp[id] = sg.qy(id, x);
}
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

    int cntp = 0;
    sg.bd(1, n);
    for (int i = 1; i <= n; i++) {
        realv[i] = (buf[i] - 1 + 1000000 - dp[i-1] % 1000000) % 1000000;
        pt[i].second = buf[i];
        if (!pos[buf[i]]) pos[buf[i]] = ++cntp;
        update_convexhull(i);
        find_min(i);
	}
    for (int i = 1; i <= n; i++)
        printf("%d %d\n", pt[i].first, realv[i]);
    for (int i = 1; i <= n; i++) {
        lb[buf[i]] = rb[buf[i]] = 0;
        dq[pos[buf[i]]].clear();
        pos[buf[i]] = 0;
    }
    segy.clear();
}
void gen_sp(int n_top, int k_top, int y_num) {
	open_file();
	n = rnd.next(1, n_top), k = rnd.next(1, k_top);
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

    int cntp = 0;
    sg.bd(1, n);
    for (int i = 1; i <= n; i++) {
        realv[i] = (pt[i].second - 1 + 1000000 - dp[i-1] % 1000000) % 1000000;
        if (!pos[pt[i].second]) pos[pt[i].second] = ++cntp;
        update_convexhull(i);
        find_min(i);
    }
    for (int i = 1; i <= n; i++)
        printf("%d %d\n", pt[i].first, realv[i]);
    for (int i = 1; i <= n; i++) {
        lb[pt[i].second] = rb[pt[i].second] = 0;
        dq[pos[pt[i].second]].clear();
        pos[pt[i].second] = 0;
    }
    segy.clear();
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

	gen_mono(200000, 1000000, true);
	gen_mono(200000, 100000, true);
	gen_mono(200000, 10000, true);
	gen_mono(200000, 1000, true);
	gen_mono(200000, 100, true);

	gen_mono(200000, 1000000, false);
	gen_mono(200000, 100000, false);
	gen_mono(200000, 10000, false);
	gen_mono(200000, 1000, false);
	gen_mono(200000, 100, false);

	gen_sp(200000, 5000, 1000);
	gen_sp(200000, 1000, 1000);
	gen_sp(200000, 500, 1000);
	gen_sp(200000, 100, 1000);
	gen_sp(200000, 10, 1000);

	gen_sp(100000, 5000, 100);
	gen_sp(100000, 1000, 100);
	gen_sp(100000, 500, 100);
	gen_sp(100000, 100, 100);
	gen_sp(100000, 10, 100);
    check_test();
}
