#ifndef A3_SRC_COMMON_CONSOLE_H_
#define A3_SRC_COMMON_CONSOLE_H_

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "matrix.h"

namespace s21 {

class Console {
 public:
  static void WriteMatrix(const Matrix&);
  static void Write(const std::string& text);
  static void WriteLine(const std::string& text);
  static void Info(const std::string& message);
  static void Error(const std::string& message);

  template <typename T>
  static void WriteVector(const std::vector<T>& vec,
                          std::string const& start = "") {
    std::stringstream ss;
    ss << start;
    for (auto const& i : vec) ss << i << " ";
    WriteLine(ss.str());
  }

  template <typename T>
  static void CheckInput(T& result) {
    while (!(std::cin >> result)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      Error("Invalid input.  Try again: ");
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  static Matrix ReadMatrix(const std::string& name);
  static int ReadInt(const std::string& message);
  static double ReadDouble(const std::string& message);
  static std::string ReadString(const std::string& message);
};

}  // namespace s21

#endif  // A3_SRC_COMMON_CONSOLE_H_
