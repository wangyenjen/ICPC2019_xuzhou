#include <validate.h>
#include <sys/resource.h>

using namespace CompLib;

const int kN = 20000, kD = 50, kL = 50;

int main() {
  struct rlimit rlim = {RLIM_INFINITY, RLIM_INFINITY};
  setrlimit(RLIMIT_STACK, &rlim);
  try {
    StdinValidator val;
    std::ios::sync_with_stdio(false);
    val.ReadLine("%u %u", "header");
    int N = val.GetLong(1, kN, "N");
    int D = val.GetLong(1, kD, "D");
    const auto kLine = GenRegex("(%u )*%u");
    for (int i = 0; i < N; i++) {
      val.ReadLine(kLine, "a_i");
      for (int j = 0; j < D; j++) val.GetLong(1, kL, "a_ij");
      val.AssertEOL();
    }
    val.AssertEnd();
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
