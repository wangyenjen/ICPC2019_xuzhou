#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;
#define F first
#define S second

pii operator+(const pii &p1, const pii &p2) {
    return make_pair(p1.F + p2.F, min(p1.S, p2.S));
}

pii _zero = {0, 0x3f3f3f3f};

struct Node {
    Node *lc, *rc;
    pii val;
    Node(): lc(NULL), rc(NULL), val(_zero){}
    void pull() {
        val = lc->val + rc->val;
    }
};

Node* Build(int L, int R) {
    Node* node = new Node();
    if (L == R) return node;
    int mid = (L + R) >> 1;
    node->lc = Build(L, mid);
    node->rc = Build(mid + 1, R);
    return node;
}

void modify(Node* node, int L, int R, int pos, int v) {
    if (L == R) {
        node->val = make_pair(v, v);
        if (v == 0) node->val = _zero;
        return;
    }
    int mid = (L + R) >> 1;
    if (pos <= mid) modify(node->lc, L, mid, pos, v);
    else modify(node->rc, mid + 1, R, pos, v);
    node->pull();
    return;
}

pii query(Node* node, int L, int R, int l, int r) {
    if (l > R || L > r) return _zero;
    else if (l <= L && R <= r) return node->val;
    int mid = (L + R) >> 1;
    return query(node->lc, L, mid, l ,r) + query(node->rc, mid+1,R, l, r);
}

const int N = 200006;
const int C = 19;

int a[N], type[N];
int cnt[N];

Node* root[C];

int main () {
    for (int i = 1; i < N; ++i) {
        cnt[i] = cnt[i >> 1] + 1;
    }
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 1; i < C; ++i) root[i] = Build(1, n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        type[i] = cnt[ a[i] ];
        modify(root[ type[i] ], 1, n, i, a[i]);
    }
    while (q--) {
        int t; scanf("%d", &t);
        if (t == 2) {
            int l, r; scanf("%d%d", &l, &r);
            ll ans = 0;
            for (int i = 1; i < C; ++i) {
                pii v = query(root[i] ,1 , n, l, r);
                if (v.F == 0) continue;
                if (ans + 1 < v.S) break;
                ans += v.F;
            }
            printf("%lld\n", ans + 1);
        }
        else if (t == 1) {
            int x, y; scanf("%d%d", &x, &y);
            modify(root[ type[x] ], 1, n, x, 0);
            a[x] = y;
            type[x] = cnt[ a[x] ];
            modify(root[ type[x] ], 1, n, x, a[x]);
        }
    }
}
 
