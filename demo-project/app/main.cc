#include <iostream>
#include <string>
#include <vector>

#include "lib/math_utils.h"
#include "lib/string_utils.h"

int main() {
  std::vector<double> prices = {99.0, 15.5, 20.0};
  double subtotal = demo::Sum(prices);
  double total = demo::ApplyTax(subtotal);

  std::cout << demo::TitleCase("bazel demo") << "\n";
  std::cout << "Subtotal: " << subtotal << "\n";
  std::cout << "Total with tax: " << total << "\n";
  return 0;
}
