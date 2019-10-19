#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define F first
#define S second
const int N = 1e6 + 87, M = 998244353;
string trim(string s) {
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == 'x') {
      if (i + 1 < s.size() && s[i + 1] == 'x') {
        s.erase(begin(s) + i);
        --i;
        continue;
      }
      if (i + 2 < s.size() && s[i + 2] == 'x') {
        s.erase(begin(s) + i);
        s.erase(begin(s) + i);
        --i;
        continue;
      }
    }
  }
  return s;
}
int dp[2][73], ans[2][N];
vector<int> g[73];
void pre() {
  for (int k = 2; k <= 3; ++k) {
    cerr << "k= " << k << endl;
    map<string, int> id;
    {
      string s;
      for (int i = 1; i <= k; ++i)
        s += char('0' + i);
      for (int i = 1; i <= k + 1; ++i)
        s += 'x';
      sort(begin(s), end(s));
      do {
        string t = trim(s);
        if (t == "x")
          continue;
        if (count(begin(t), end(t), '1') == 0)
          continue;
        if (!id.count(t)) {
          int fuck = id.size();
          id[t] = fuck;
          cerr << t << ' ' << id[t] << endl;
        }
      } while (next_permutation(begin(s), end(s)));
    }
    const int m = id.size();
    cerr << "M=" << m << endl;
    for (int i = 0; i < m; ++i)
      g[i].clear();
    memset(dp, 0, sizeof dp);
    set<int> tt;
    for (const auto &p : id) {
      const string &s = p.first;
      int x = p.second;
      if (s.size() == k + 1 && count(begin(s), end(s), 'x') == 1) {
        dp[(k + 1) % 2][x] = 1;
      }
      for (int i = 0; i <= s.size(); ++i)
        if ((i == s.size() || isdigit(s[i])) && (i == 0 || isdigit(s[i - 1]))) {
          string t = s;
          t.insert(begin(t) + i, '0');
          for (auto &c : t)
            if (isdigit(c)) {
              ++c;
              if (c > '0' + k)
                c = 'x';
            }
          t = trim(t);
          assert(id.count(t));
          int y = id[t];
          g[x].push_back(y);
          tt.insert(y);
        }
      assert(g[x].size());
      if (g[x].size() == 0)
        cerr << "MUDA " << s << ' ' << endl;
    }
    assert(tt.size() == m);
    for (int i = k + 1; i + 1 < N; ++i) {
      int a = i % 2;
      int b = 1 ^ a;
      fill_n(dp[b], m, 0);
      for (int j = 0; j < m; ++j)
        for (int x : g[j])
          (dp[b][x] += dp[a][j]) %= M;
      ans[k - 2][i + 1] = accumulate(dp[b], dp[b] + m, 0ll) % M;
    }
  }
}
int solve(int n, int k) {
  if (k == 1) {
    return 1 + (n > 1);
  } else if (n <= k + 1) {
    int p = 1;
    for (int j = 1; j <= n; ++j)
      p *= j;
    return p;
  } else {
    return ans[k - 2][n];
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  pre();
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    cout << solve(n, k) << '\n';
  }
}
