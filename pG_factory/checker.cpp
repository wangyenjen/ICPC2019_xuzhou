#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <validate.h>

using namespace CompLib;

const int kN = 20000, kD = 50, kL = 100;
const long double kEps = 1e-2;

int main(int argc, char** argv) {
  try {
    std::ifstream fout(argv[2]), fans(argv[3]);
    Validator val(fout);
    long double ans, output;
    val.ReadLine("%e", "answer");
    output = val.Get<long double>();
    val.AssertEnd();
    fans >> ans;

    if (!std::isnormal(output)) {
      throw std::invalid_argument("Not a normal number");
    }
    long double err = std::fabs(output - ans) / ans;
    std::cerr << std::setprecision(3) << std::scientific;
    std::cerr << "Relative error: " << err << '\n';
    if (err > kEps) throw std::invalid_argument("WA");
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
