/// Author: Yen-Jen Wang
#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

int RandInt(int lower_bound, int upper_bound) {
  return rnd.next(lower_bound, upper_bound);
}

string IntToString(int x) {
	string res = "";
  if (x == 0) {
    res = "0";
  } else {
    while (x) {
      res += (char)(x % 10 + '0');
      x /= 10;
    }
  }
  reverse(res.begin(), res.end());
  return res;
}

void SaveData(const string& tag, 
    const int& id,
    const int& n,
    const int &b,
    const int &m,
    const vector<int>& a,
    const vector<vector<pair<int, int> > >& qs) {
  const string& name_in = "./../data/" + tag + "-" + IntToString(id) + ".in";
  const string& name_ans = "./../data/" + tag + "-" + IntToString(id) + ".ans";
  FILE *fp = fopen(name_in.c_str(), "w");
  fprintf(fp, "%d %d %d\n", n, b, m);
  for (int i = 0; i < n; i++) {
    fprintf(fp, "%d%c", a[i], " \n"[i == n - 1]);
  }
  for (const vector<pair<int, int> >& v : qs) {
    fprintf(fp, "%d", (int)v.size());
    for (const pair<int, int> &p : v) {
      fprintf(fp, " %d %d", p.first, p.second);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);

  char order[512];
  sprintf(order, "./../sol < %s > %s", name_in.c_str(), name_ans.c_str());
  system(order);
}

void BuildSmall() {
  {
    int id = 0;
    for (int N = 3; N <= 15; N++) {
      for (int B = 2; B <= max(2, N / 3); B++) {
        vector<int> a;
        for (int i = 0; i < N; i++) {
          a.push_back(RandInt(1, B));
        }
        vector<vector<pair<int, int> > > qs;
        for (int l = 1; l <= N; l++) {
          for (int r = l; r <= N; r++) {
            qs.push_back({make_pair(l, r)});
          }
        }
        SaveData("small-K_is_1", ++id, N, B, (int)qs.size(), a, qs);
      }
    }
  }

  {
    int id = 0;
    for (int N = 3; N <= 15; N++) {
      for (int B = 2; B <= max(2, N / 3); B++) {
        vector<int> a;
        for (int i = 0; i < N; i++) {
          a.push_back(RandInt(1, B));
        }
        vector<vector<pair<int, int> > > qs;
        for (int times = 0; times < 3000; times++) {
          int K = RandInt(2, 2 * N);
          vector<pair<int, int> > vs;
          while (K--) {
            int l = RandInt(1, N);
            int r = RandInt(l, N);
            vs.emplace_back(l, r);
          }
          qs.push_back(vs);
        }
        SaveData("small-random", ++id, N, B, (int)qs.size(), a, qs);
      }
    }
  }

  {
    const int N = 100;
    const int B = 100000;
    const int id = 1;
    vector<int> nums = {1, B};
    for (int i = 0; i < 20; i++) {
      nums.push_back(RandInt(1, B));
    }
    vector<int> a;
    for (int i = 0; i < N; i++) {
      a.push_back(nums[RandInt(0, (int)nums.size() - 1)]);
    }
    vector<vector<pair<int, int> > > qs;
    for (int times = 0; times < 1000; times++) {
      int K = RandInt(2, N);
      vector<pair<int, int> > vs;
      while (K--) {
        int l = RandInt(1, N);
        int r = RandInt(l, N);
        vs.emplace_back(l, r);
      }
      qs.push_back(vs);
    }
    SaveData("small-random-B_is_large", id, N, B, (int)qs.size(), a, qs);
  }

}

void BuildBig() {
  const int N = 100000;
  const int B = 100000;
  const int SQRT_N = 316;
  {
    const int M = 100000;
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 0; i < N; i++) {
        a.push_back(RandInt(0, 1) ? B : 1);
      }
      vector<vector<pair<int, int> > > qs;
      for (int i = 0; i < M; i++) {
        int l = RandInt(1, N);
        int r = RandInt(l, N);
        qs.push_back({make_pair(l, r)});
      }
      SaveData("big-random-real_B_is_2-K_is_1", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    const int M = 100000;
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 0; i < N; i++) {
        a.push_back(RandInt(0, 1) ? B : 1);
      }
      vector<vector<pair<int, int> > > qs;
      for (int i = 0; i < M; i++) {
        int l = RandInt(1, SQRT_N);
        int r = RandInt(N - SQRT_N, N);
        qs.push_back({make_pair(l, r)});
      }
      SaveData("big-small_range_random-real_B_is_2-K_is_1", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    const int M = SQRT_N;
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 0; i < N; i++) {
        a.push_back(RandInt(B - SQRT_N, B));
      }
      vector<vector<pair<int, int> > > qs;
      for (int i = 0; i < M; i++) {
        int K = SQRT_N;
        vector<pair<int, int> > vs;
        while (K--) {
          int l = RandInt(1, SQRT_N);
          int r = RandInt(N - SQRT_N, N);
          vs.emplace_back(l, r);
        }
        qs.push_back(vs);
      }
      SaveData("big-random-everything_is_sqrt_n", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    const int M = SQRT_N;
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 0; i < N; i++) {
        a.push_back(RandInt(0, 1) ? B : 1);
      }
      vector<vector<pair<int, int> > > qs;
      for (int i = 0; i < M; i++) {
        int K = SQRT_N;
        vector<pair<int, int> > vs;
        while (K--) {
          int l = RandInt(1, SQRT_N);
          int r = RandInt(N - SQRT_N, N);
          vs.emplace_back(l, r);
        }
        qs.push_back(vs);
      }
      SaveData("big-random-everything_is_sqrt_n-real_B_is_2", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 0; i < N; i++) {
        a.push_back(RandInt(0, 1) ? B : 1);
      }
      vector<vector<pair<int, int> > > qs;
      int k_lim = 100000, K = 1;
      while (k_lim > 0) {
        K = min(K + 1, k_lim);
        k_lim -= K;
        vector<pair<int, int> > vs;
        for (int i = 0; i < K; i++) {
          int l = RandInt(1, SQRT_N);
          int r = RandInt(N - SQRT_N, N);
          vs.emplace_back(l, r);
        }
        qs.push_back(vs);
      }
      SaveData("big-random-K_is_different-real_B_is_2", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 0; i < N; i++) {
        a.push_back(RandInt(B - SQRT_N, B));
      }
      vector<vector<pair<int, int> > > qs;
      int k_lim = 100000, K = 1;
      while (k_lim > 0) {
        K = min(K + 1, k_lim);
        k_lim -= K;
        vector<pair<int, int> > vs;
        for (int i = 0; i < K; i++) {
          int l = RandInt(1, SQRT_N);
          int r = RandInt(N - SQRT_N, N);
          vs.emplace_back(l, r);
        }
        qs.push_back(vs);
      }
      SaveData("big-random-K_is_different-real_B_is_sqrt", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 0; i < N; i++) {
        a.push_back(RandInt(B - SQRT_N, B));
      }
      vector<vector<pair<int, int> > > qs;
      int k_lim = 100000;
      while (k_lim > 0) {
        int K = RandInt(1, k_lim);
        k_lim -= K;
        vector<pair<int, int> > vs;
        while (K--) {
          int l = RandInt(1, SQRT_N);
          int r = RandInt(N - SQRT_N, N);
          vs.emplace_back(l, r);
        }
        qs.push_back(vs);
      }
      SaveData("big-random-K_is_random-real_B_is_sqrt", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 0; i < N; i++) {
        a.push_back(RandInt(0, 1) ? B : 1);
      }
      vector<vector<pair<int, int> > > qs;
      int k_lim = 100000;
      while (k_lim > 0) {
        int K = RandInt(1, k_lim);
        k_lim -= K;
        vector<pair<int, int> > vs;
        while (K--) {
          int l = RandInt(1, SQRT_N);
          int r = RandInt(N - SQRT_N, N);
          vs.emplace_back(l, r);
        }
        qs.push_back(vs);
      }
      SaveData("big-random-K_is_random-real_B_is_2", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 1; i <= N; i++) {
        a.push_back(i);
      }
      for (int i = 1; i < N; i++) {
        swap(a[i], a[RandInt(0, i - 1)]);
      }
      vector<vector<pair<int, int> > > qs;
      int k_lim = 100000;
      while (k_lim > 0) {
        int K = RandInt(1, k_lim);
        k_lim -= K;
        vector<pair<int, int> > vs;
        while (K--) {
          int l = RandInt(1, SQRT_N);
          int r = RandInt(N - SQRT_N, N);
          vs.emplace_back(l, r);
        }
        qs.push_back(vs);
      }
      SaveData("big-random-K_is_random", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    const int M = 100000;
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 1; i <= N; i++) {
        a.push_back(i);
      }
      for (int i = 1; i < N; i++) {
        swap(a[i], a[RandInt(0, i - 1)]);
      }
      vector<vector<pair<int, int> > > qs;
      for (int i = 0; i < M; i++) {
        int l = RandInt(1, SQRT_N);
        int r = RandInt(N - SQRT_N, N);
        qs.push_back({make_pair(l, r)});
      }
      SaveData("big-small_range_random-a_is_permutation", ++id, N, B, (int)qs.size(), a, qs);
    }
  }

  {
    const int M = SQRT_N;
    int id = 0;
    for (int times = 0; times < 3; times++) {
      vector<int> a;
      for (int i = 1; i <= N; i++) {
        a.push_back(i);
      }
      for (int i = 1; i < N; i++) {
        swap(a[i], a[RandInt(0, i - 1)]);
      }
      vector<vector<pair<int, int> > > qs;
      for (int i = 0; i < M; i++) {
        int K = SQRT_N;
        vector<pair<int, int> > vs;
        while (K--) {
          int l = RandInt(1, SQRT_N);
          int r = RandInt(N - SQRT_N, N);
          vs.emplace_back(l, r);
        }
        qs.push_back(vs);
      }
      SaveData("big-random-everything_is_sqrt_n-a_is_permutation", ++id, N, B, (int)qs.size(), a, qs);
    }
  }
}

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);
  BuildSmall();
  BuildBig();
  return 0;
}
