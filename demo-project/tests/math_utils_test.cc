#include <cmath>
#include <iostream>
#include <vector>

#include "lib/math_utils.h"

namespace {

bool NearlyEqual(double a, double b) {
  return std::fabs(a - b) < 1e-9;
}

}  // namespace

int main() {
  std::vector<double> values = {10.0, 20.0, 30.0};
  double sum = demo::Sum(values);
  if (!NearlyEqual(sum, 60.0)) {
    std::cerr << "Expected sum 60.0 but got " << sum << "\n";
    return 1;
  }

  double taxed = demo::ApplyTax(100.0);
  if (!NearlyEqual(taxed, 107.0)) {
    std::cerr << "Expected taxed 107.0 but got " << taxed << "\n";
    return 1;
  }

  std::cout << "All math_utils tests passed.\n";
  return 0;
}
