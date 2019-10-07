#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <validate.h>

using namespace CompLib;

const long double kEps = 1e-6;

int main(int argc, char** argv) {
  try {
    std::ifstream fin(argv[1]), fout(argv[2]), fans(argv[3]);
    int K;
    fin >> K >> K >> K;
    K = 1 << K;
    Validator val(fout);
    long double ans, output;
    for (int i = 0; i < K; i++) {
      val.ReadLine("%e", "answer");
      output = val.Get<long double>();
      fans >> ans;
      if (!std::isfinite(output)) {
        throw std::invalid_argument("Not a normal number");
      }
      long double err = std::fabs(output - ans) / std::max(ans, (long double)1);
      if (err > kEps) throw std::invalid_argument("WA");
    }
    val.AssertEnd();
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
