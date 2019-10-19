#include <bits/stdc++.h>
using namespace std;
constexpr int T = 200;
constexpr int N = 5000;
typedef long long LL;
unordered_map<LL, int> root3;
bool hard[T + 1];
int hard_list[] = {30, 33, 39, 51, 52, 74, 75, 84, 87, 102, 108, 110, 111, 114, 138, 143, 150, 156, 159, 165, 172, 173, 180, 195};
int hard_list1000[] = {30, 33, 39, 52, 74, 75, 84, 87, 108, 110, 114, 143, 156, 165, 172, 173, 180, 195};
int hard_list5000[] = {30, 33, 39, 52, 74, 75, 84, 110, 114, 143, 156, 165, 172, 173, 180, 195};
int main() {
  for (auto hard_number: hard_list) {
    hard[hard_number] = true;
  }
  FILE *f = fopen("sol.cpp", "w");
  for (LL i = -N; i <= N; ++i) {
    root3[i * i * i] = i;
  }
  fprintf(f, "#include <bits/stdc++.h>\n");
  fprintf(f, "using namespace std;\n");
  fprintf(f, "typedef long long LL;\n");
  fprintf(f, "constexpr int N = 201;\n");
  fprintf(f, "LL ans[N][3];\n");
  fprintf(f, "LL cube(LL x) {\n");
  fprintf(f, "  return x * x * x;\n");
  fprintf(f, "}\n");
  fprintf(f, "int main() {\n");

  LL bnd = 0;
  vector<int> not_found;
  for (int x = 0; x <= T; ++x) {
    if (x % 9 == 4 or x % 9 == 5 or x == 42) {
      continue;
    }
    if (x % 10 == 0) {
      fprintf(stderr, "trying %d\n", x);
    }
    bool got = false;
    int abs_value = hard[x] ? N : 100;
    for (LL i = -abs_value; i <= abs_value and not got; ++i) {
      for (LL j = i; j <= abs_value and not got; ++j) {
        LL iii = i * i * i;
        LL jjj = j * j * j;
        LL goal = x - iii - jjj;
        auto it = root3.find(goal);
        if (it == root3.end()) {
          continue;
        }
        got = true;
        fprintf(f, "ans[%d][0] = %lld;\n", x, i);
        fprintf(f, "ans[%d][1] = %lld;\n", x, j);
        fprintf(f, "ans[%d][2] = %d;\n", x, it->second);

        bnd = max(bnd, abs(i));
        bnd = max(bnd, abs(j));
        bnd = max(bnd, (LL)abs(it->second));
      }
    }
    if (not got) {
      fprintf(stderr, "%d not found\n", x);
      not_found.push_back(x);
    }
  }

  fprintf(f, "  int q; cin >> q; while (q--) {\n");
  fprintf(f, "    int x; cin >> x;\n");
  fprintf(f, "    if (cube(ans[x][0]) + cube(ans[x][1]) + cube(ans[x][2]) == x) {\n");
  fprintf(f, "      cout << ans[x][0] << \" \";\n");
  fprintf(f, "      cout << ans[x][1] << \" \";\n");
  fprintf(f, "      cout << ans[x][2] << \"\\n\";\n");
  fprintf(f, "    } else {\n");
  fprintf(f, "      cout << \"impossible\" << \"\\n\";\n");
  fprintf(f, "    }\n");
  fprintf(f, "  }\n");
  fprintf(f, "}\n");
  fclose(f);

  fprintf(stderr, "Max used abs value: %lld\n", bnd);
  fprintf(stderr, "%lld possible solutions not found\n", (LL)not_found.size());
  for (size_t i = 0; i < not_found.size(); ++i) {
    if (i) {
      fprintf(stderr, ", ");
    }
    fprintf(stderr, "%d", not_found[i]);
  }
  fprintf(stderr, "\n");
}
