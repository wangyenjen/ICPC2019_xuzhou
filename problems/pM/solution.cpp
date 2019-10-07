/*
這是一題根號題。

對於詢問，現在假設有兩種作法：
1. 對於詢問長度 > K 的，使用以下方法：對於每個序列，做兩次二分搜尋，花費時間是 O(N / K * log N)
2. 對於詢問長度 < K 的，開一個表格紀錄少了哪兩個 index 的所有 hash 值。複雜度為 O(K^2 log N)

經過簡單數學運算，可以發現當 K = N^{1/3} 時，有最佳解 O(N^{4/3} log N)。

hash 的值域可能要到 long long 範圍！
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;
typedef pair<pi, ll> pii;
#define F first.first
#define S first.second
#define T second
const int N = 100006;
const ll X1 = 880301;
const ll X2 = 991;
const ll X3 = 32183;
const ll mod1 = 1000000123;
const ll mod2 = 1000000891;
const ll mod3 = 998244353;

#define SZ(x) ((int)(x).size())

pii ppow[N];

pii operator+(const pii &p1, const pii &p2) {
    return make_pair(make_pair((p1.F + p2.F) % mod1, (p1.S + p2.S) % mod2), (p1.T + p2.T) % mod3);
}

pii operator-(const pii &p1, const pii &p2) {
    return make_pair(make_pair((p1.F - p2.F + mod1) % mod1, (p1.S - p2.S + mod2) % mod2), (p1.T - p2.T + mod3) % mod3);
}

pii operator*(const pii &p1, const pii &p2) {
    return make_pair(make_pair((p1.F * p2.F) % mod1, (p1.S * p2.S) % mod2), (p1.T * p2.T) % mod3);
}

vector<pii> pre[N];
vector<pii> hash_vals[N];
vector<int> ids[N];

pii e = make_pair(make_pair(0, 0), 0);

vector<int> s[N];

pii hash_val(int id, int L, int R) {
    //[L, R], zero base !!!
    return (pre[id][R] - (L ? pre[id][L - 1] : e)) * ppow[N - R - 2];
}

const int K = 56;

vector<pii> hashs[K][K]; //hashs[i][j]: hash val of delete i and j

pii Val(int x) {
    return make_pair(make_pair(x, x), x);
}

void build(int id) {
    for (int i = 0; i < SZ(s[id]); ++i) {
        pre[id].push_back( (i ? pre[id].back() : e ) + (Val(s[id][i]) * ppow[i]));
    }
    hash_vals[ SZ(s[id]) ].push_back(pre[id].back());
    ids[ SZ(s[id]) ].push_back(id);
    if (SZ(s[id]) < K) {
        for (int i = 0; i < SZ(s[id]); ++i) {
            for (int j = i; j < SZ(s[id]); ++j) {
                if (i == j) {
                    hashs[i][i].push_back(pre[id].back() - (Val(s[id][i]) * ppow[i]));
                }
                else {
                    hashs[i][j].push_back(pre[id].back() - ((Val(s[id][i]) * ppow[i]) + (Val(s[id][j]) * ppow[j])));
                }
            }
        }
    }
}

int Cnt(vector<pii> &v, pii val) {
    return upper_bound(v.begin(), v.end(), val) - lower_bound(v.begin(), v.end(), val);
}

void input(vector<int> &s) {
    int sz; cin >> sz;
    while (sz--) {
        int x; cin >> x;
        s.push_back(x);
    }
}

int solve_ans = 0;

inline void yes() {
    ++solve_ans;
}

void solve(int m) {
    solve_ans = 0;
    vector<int> q; input(q); //cin >> s;
    int n = SZ(q);
    pii val = e;
    for (int i = 0; i < n; ++i) {
        val = val + (Val(q[i]) * ppow[i]);
    }
    if (SZ(q) < K) {
        int _0 = Cnt(hash_vals[n], val);
        int _1 = 0, _2 = 0;
        for (int i = 0; i < n; ++i) {
            _1 += Cnt(hashs[i][i], val - (Val(q[i]) * ppow[i]));
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                _2 += Cnt(hashs[i][j], val - ((Val(q[i]) * ppow[i]) + (Val(q[j]) * ppow[j])));
            }
        }
        
        //cout << "_0 = " << _0 << " , _1 = " << _1 << " , _2 = " << _2 << endl;
        _1 -= _0 * n;
        _2 -= n * (n - 1) / 2 * _0 + (n - 1) * _1;
        //solve_ans = (_0) + (_1 - _0 * n) + (_2 - _0 * (n * (n - 1) / 2))
        //cout << "_0 = " << _0 << " , _1 = " << _1 << " , _2 = " << _2 << endl;
        solve_ans = _0 + _1 + _2;
    }
    else {
        pre[m].clear();
        for (int i = 0; i < n; ++i) {
            pre[m].push_back( (i ? pre[m].back() : e ) + (make_pair(make_pair(q[i], q[i]), q[i]) * ppow[i]) );
        }
        for (int id: ids[n]) {
            int now = 0;
            int l = -1, r = n;
            while (r - l != 1) {
                int mid = (l + r) >> 1;
                if (hash_val(m, now, mid) == hash_val(id, now, mid)) l = mid;
                else r = mid;
            }
            if (r == n) {
                yes();
                continue;
            }
            now = r + 1;
            l = now - 1, r = n;
            while (r - l != 1) {
                int mid = (l + r) >> 1;
                if (hash_val(m, now, mid) == hash_val(id, now, mid)) l = mid;
                else r = mid;
            }
            if (r == n) {
                yes();
                continue;
            }
            now = r + 1;
            if (now == n || hash_val(m, now, n - 1) == hash_val(id, now, n - 1)) {
                yes();
                continue;
                //return;
            }
        }
        //no();
        //return;
    }
    cout << solve_ans << '\n';
    //printf("%d\n", solve_ans);
    //cout << solve_ans << endl;
}

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    ppow[0] = make_pair(make_pair(1, 1), 1);
    for (int i = 1; i < N; ++i) {
        ppow[i] = (ppow[i - 1] * make_pair(make_pair(X1, X2), X3));
    }
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        /*int sz; cin >> sz;
        while (sz--) {
            int x; cin >> x;
            s[i].push_back(x);
        }*/
        input(s[i]);
        //cin >> s[i];
        build(i);
    }
    for (int i = 0; i < N; ++i) {
        vector<pii> &v = hash_vals[i];
        sort(v.begin(), v.end());
    }
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            vector<pii> &v = hashs[i][j];
            sort(v.begin(), v.end());
        }
    }
    int q; cin >> q;
    while (q--) {
        solve(n + 1);
    }
}


