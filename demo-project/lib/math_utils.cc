#include "lib/math_utils.h"

namespace demo {

double Sum(const std::vector<double>& values) {
  double total = 0.0;
  for (double value : values) {
    total += value;
  }
  return total;
}

double ApplyTax(double amount) {
  return amount * 1.07;
}

}  // namespace demo
