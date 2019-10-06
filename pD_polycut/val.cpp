/*
 * Not checking the convex polygon property
 */

#include <validate.h>
#include <sys/resource.h>

using namespace CompLib;

const int kM = 30000, kT = 10000, kL = 1'000'000'000, kK = 3;

int main() {
  struct rlimit rlim = {RLIM_INFINITY, RLIM_INFINITY};
  setrlimit(RLIMIT_STACK, &rlim);
  try {
    StdinValidator val;
    std::ios::sync_with_stdio(false);
    val.ReadLine("%u %u %u", "header");
    int N = val.GetLong(1, kM, "N");
    int M = val.GetLong(1, kM, "M");
    int K = val.GetLong(1, kK, "K");
    const auto kLine1 = GenRegex("%d %d %d");
    for (int i = 0; i < N; i++) {
      val.ReadLine(kLine1, "pt");
      val.GetLong(-kT, kT, "x");
      val.GetLong(-kT, kT, "y");
      val.GetLong(-kT, kT, "z");
    }
    const auto kLine2 = GenRegex("%u %u");
    for (int i = 0; i < M; i++) {
      val.ReadLine(kLine2, "ed");
      val.GetLong(0, N - 1, "u");
      val.GetLong(0, N - 1, "v");
    }
    for (int i = 0; i < K; i++) {
      val.ReadLine("%d %d %d %d", "pl");
      val.GetLong(-kL, kL, "a");
      val.GetLong(-kL, kL, "b");
      val.GetLong(-kL, kL, "c");
      val.GetLong(-kL, kL, "d");
    }
    val.AssertEnd();
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
