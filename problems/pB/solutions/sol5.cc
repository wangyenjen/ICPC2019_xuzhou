#include <bits/stdc++.h>
using namespace std;

const int kN = 1e6 + 1;
const int kMod = 998244353;
constexpr int kState[4] = {0, 0, 12, 68};
constexpr int kRecurrence[4] = {0, 0, 70, 70};
int tab[kN][2], rec[500][500], tr[70][70];
string cache[500];
vector<int> suc[70];

map<string, int> z;

int GetID(const string &s) {
  if (z.find(s) != z.end())
    return z[s];
  int res = z.size();
  cache[res] = s;
  return z[s] = res;
}

template <int K> array<int, kState[K]> Perm() {
  vector<int> v(K);
  iota(v.begin(), v.end(), 0);
  array<int, kState[K]> res{};
  do {
    string s = "";
    for (int i = 0; i < K; ++i)
      s += (char)(v[i] + '0');
    res[GetID(s)] = 1;
  } while (next_permutation(v.begin(), v.end()));
  return res;
}

template <int K> int Insert(const string &s, int r, int pos) {
  if (rec[r][pos] != -1)
    return rec[r][pos];
  string res = "";
  for (int i = 0; i < pos; ++i) {
    if (s[i] == 'x' || s[i] - '0' == K - 1)
      res += 'x';
    else
      res += s[i] + 1;
  }
  res += '0';
  for (int i = pos; i < (int)s.size(); ++i) {
    if (s[i] == 'x' || s[i] - '0' == K - 1)
      res += 'x';
    else
      res += s[i] + 1;
  }
  string trim = "";
  for (int i = 0, j; i < (int)res.size(); i = j) {
    if (res[i] != 'x') {
      trim += res[i];
      j = i + 1;
    } else {
      for (j = i; j < (int)res.size() && res[j] == 'x'; ++j)
        ;
      trim += 'x';
    }
  }
  return rec[r][pos] = GetID(trim);
}

int fpow(int a, int n, int p) {
  int res = 1;
  while (n > 0) {
    if (n & 1)
      res = 1LL * res * a % p;
    a = 1LL * a * a % p;
    n >>= 1;
  }
  return res;
}

template <int P> vector<int> BerlekampMassey(vector<int> x) {
  vector<int> cur, ls;
  int lf = 0, ld = 0;
  for (int i = 0; i < (int)x.size(); ++i) {
    int t = 0;
    for (int j = 0; j < (int)cur.size(); ++j)
      (t += 1LL * cur[j] * x[i - j - 1] % P) %= P;
    if (t == x[i])
      continue;
    if (cur.empty()) {
      cur.resize(i + 1);
      lf = i, ld = (t + P - x[i]) % P;
      continue;
    }
    int k = 1LL * fpow(ld, P - 2, P) * (t + P - x[i]) % P;
    vector<int> c(i - lf - 1);
    c.push_back(k);
    for (int j = 0; j < (int)ls.size(); ++j)
      c.push_back(1LL * k * (P - ls[j]) % P);
    if (c.size() < cur.size())
      c.resize(cur.size());
    for (int j = 0; j < (int)cur.size(); ++j)
      c[j] = (c[j] + cur[j]) % P;
    if (i - lf + (int)ls.size() >= (int)cur.size()) {
      ls = cur, lf = i;
      ld = (t + P - x[i]) % P;
    }
    cur = c;
  }
  return cur;
}

template <int K> void Build() {
  z.clear();
  memset(cache, 0, sizeof(cache));
  memset(rec, -1, sizeof(rec));
  memset(tr, 0, sizeof(tr));
  array<int, kState[K]> dp = Perm<K>();
  for (int i = K + 1; i <= kRecurrence[K]; ++i) {
    vector<pair<int, int>> tran;
    for (int p = 0; p < kState[K]; ++p) {
      string &s = cache[p];
      if (s.empty())
        continue;
      for (int j = 0; j <= (int)s.size(); ++j) {
        bool ok =
            (j == (int)s.size() || s[j] != 'x') && (j == 0 || s[j - 1] != 'x');
        if (ok) {
          int o = Insert<K>(s, p, j);
          if (i == 10)
            tr[p][o]++;
          tran.emplace_back(o, dp[p]);
        }
      }
    }
    sort(tran.begin(), tran.end());
    fill(dp.begin(), dp.end(), 0);
    int total = 0;
    for (int j = 0, k; j < (int)tran.size(); j = k) {
      int sum = 0;
      for (k = j; k < (int)tran.size() && tran[k].first == tran[j].first; ++k)
        (sum += tran[k].second) %= kMod;
      dp[tran[j].first] = sum;
      (total += sum) %= kMod;
    }
    if (K == 2)
      tab[i][0] = total;
    else
      tab[i][1] = total;
  }
  vector<int> s(kRecurrence[K]);
  for (int i = 0; i < K; ++i) {
    if (i == 0)
      s[i] = tab[i + 1][K - 2] = 1;
    if (i == 1)
      s[i] = tab[i + 1][K - 2] = 2;
    if (i == 3)
      s[i] = tab[i + 1][K - 2] = 6;
  }
  for (int i = K; i < kRecurrence[K]; ++i)
    s[i] = tab[i + 1][K - 2];
  vector<int> rec = BerlekampMassey<kMod>(s);
  for (int i = kRecurrence[K] + 1; i < kN; ++i) {
    tab[i][K - 2] = 0;
    for (int j = 0; j < (int)rec.size(); ++j)
      (tab[i][K - 2] += 1LL * rec[j] * tab[i - j - 1][K - 2] % kMod) %= kMod;
  }
}

void Init() {
  Build<2>();
  Build<3>();
}

int main() {
  Init();
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, k;
    scanf("%d%d", &n, &k);
    if (k == 1) {
      if (n == 1)
        printf("1\n");
      else
        printf("2\n");
    }
    if (k == 2) {
      if (n == 1)
        printf("1\n");
      else if (n == 2)
        printf("2\n");
      else
        printf("%d\n", tab[n][0]);
    }
    if (k == 3) {
      if (n == 1)
        printf("1\n");
      else if (n == 2)
        printf("2\n", 2);
      else if (n == 3)
        printf("6\n", 6);
      else
        printf("%d\n", tab[n][1]);
    }
  }
  return 0;
}
