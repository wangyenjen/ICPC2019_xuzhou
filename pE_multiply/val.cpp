#include <validate.h>
#include <sys/resource.h>

using namespace CompLib;

const int kN = 100000, kT = 8;
const long long kX = 1'000'000'000'000'000'000;

int main() {
  struct rlimit rlim = {RLIM_INFINITY, RLIM_INFINITY};
  setrlimit(RLIMIT_STACK, &rlim);
  try {
    StdinValidator val;
    std::ios::sync_with_stdio(false);
    const auto kLine1 = GenRegex("%u %u %u");
    const auto kLine2 = GenRegex("(%u )*%u");
    val.ReadLine("%u", "T");
    int T = val.GetLong(1, kT, "T");
    while (T--) {
      val.ReadLine(kLine1, "header");
      int N = val.GetLong(1, kN, "N");
      val.GetLong(1, kX, "X");
      long long Y = val.GetLong(1, kX, "Y");
      val.ReadLine(kLine2, "a");
      long long sum = 0;
      for (int j = 0; j < N; j++) sum += val.GetLong(1, kX, "a_i");
      val.AssertEOL();
      if (sum >= Y) throw std::invalid_argument("Sum(a_i) >= Y");
    }
    val.AssertEnd();
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
