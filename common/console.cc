#include "console.h"

namespace s21 {

void Console::WriteMatrix(const Matrix& matrix) {
  std::stringstream ss;
  for (int i = 0; i < matrix.Rows(); ++i) {
    for (int j = 0; j < matrix.Cols(); ++j) {
      ss.width(3);
      ss << matrix(i, j) << " ";
    }
    ss << std::endl;
  }
  std::cout << ss.str() << std::endl;
}

void Console::Write(const std::string& text) {
  std::cout << "\033[0;32m" << text << "\033[0m";
}

void Console::WriteLine(const std::string& text) { Write(text + "\n"); }

void Console::Info(const std::string& message) {
  std::cout << "\033[0;36m" << message << "\033[0m";
}

void Console::Error(const std::string& message) {
  std::cout << "\033[0;31m[ERROR]\033[0m - " << message << std::endl;
}

Matrix Console::ReadMatrix(const std::string& name) {
  int rows = ReadInt("Matrix " + name + " rows: ");
  int cols = ReadInt("Matrix " + name + " columns: ");

  Matrix result(rows, cols);

  if (rows < 1 || cols < 1) return result;

  int mode = ReadInt("Enter mode\n0 - randomly\n* - manually\n> ");
  if (mode != 0) {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        std::stringstream ss;
        ss << "row " << i + 1 << " column " << j + 1 << ": ";
        result(i, j) = ReadDouble(ss.str());
      }
    }
  } else {
    result.FillRandomly(1, 10);
  }

  return result;
}

int Console::ReadInt(const std::string& message) {
  Info(message);

  int result = 0;
  CheckInput(result);
  return result;
}

double Console::ReadDouble(const std::string& message) {
  Info(message);

  double result = 0;
  CheckInput(result);
  return result;
}

std::string Console::ReadString(const std::string& message) {
  Info(message);

  std::string result;
  CheckInput(result);
  return result;
}

}  // namespace s21
