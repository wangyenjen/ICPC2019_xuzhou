#include "testlib.h"
using namespace std;

typedef long long LL;
constexpr int T = 10;
constexpr int N = 200;
constexpr int V = 5000;

LL cube(LL x) {
  return x * x * x;
}

int main(int argc, char** argv) {
  registerTestlibCmd(argc, argv);

  int t = inf.readInt(1, T, "T");
  inf.readEoln();

  for (int _ = 0; _ < t; ++_) {
    int x = inf.readInt(0, N, "N");
    bool judge_ans = true, contestant_ans = true;
    while (true) {
      string _a = ans.readString();
      if (_a == "impossible") {
        judge_ans = false;
        break;
      }
      stringstream ss(_a);
      LL a, b, c;
      try {
        ss >> a >> b >> c;
      } catch(std::exception& e) {
        break;
      }
      break;
    }
    while (true) {
      string _a = ouf.readString();
      if (_a == "impossible") {
        contestant_ans = false;
        break;
      }
      stringstream ss(_a);
      LL a, b, c;
      try {
        ss >> a >> b >> c;
      } catch(std::exception& e) {
        quitf(_wa, "Fail to read numbers");
        break;
      }
      if (abs(a) > V or abs(b) > V or abs(c) > V) {
        quitf(_wa, "value exceed %lld.", (LL)V);
        break;
      }
      LL _result = cube(a) + cube(b) + cube(c);
      if (_result != x) {
        quitf(_wa, "Given cube doesn't sum up to x(a=%lld, b=%lld, c=%lld, x=%d)", a, b, c, x);
        break;
      }
      break;
    }
    if (judge_ans == contestant_ans) {
      continue;
    }
    if (judge_ans and not contestant_ans) {
      quitf(_wa, "Judge found solution but not contestant");
    }
    if (not judge_ans and contestant_ans) {
      quitf(_wa, "Contestant found solution but not judge!!!!!!");
    }
  }

  quitf(_ok, "OK!");
}
