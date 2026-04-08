#include "lib/string_utils.h"

#include <cctype>

namespace demo {

std::string TitleCase(const std::string& input) {
  std::string result = input;
  bool new_word = true;

  for (char& c : result) {
    if (std::isspace(static_cast<unsigned char>(c))) {
      new_word = true;
      continue;
    }
    if (new_word) {
      c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
      new_word = false;
    }
  }

  return result;
}

}  // namespace demo
