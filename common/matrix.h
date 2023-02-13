#ifndef COMMON_MATRIX_H_
#define COMMON_MATRIX_H_

#include <random>

namespace s21 {

class Matrix {
 public:
  Matrix(int rows, int cols);
  ~Matrix();
  Matrix(const Matrix&);
  Matrix(Matrix&&);
  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&&);

  int Rows() const { return rows_; }
  int Cols() const { return cols_; }

  double operator()(int row, int col) const;
  double& operator()(int row, int col);

  void FillRandomly(int from, int to);

  template <typename T>
  T Random(T from, T to) {
    std::random_device rd;
    std::uniform_int_distribution<T> uniform_dist(from, to);
    return uniform_dist(rd);
  }

 private:
  int rows_ = 0;
  int cols_ = 0;
  double* data_ = nullptr;

  void Init();
  void Copy(const Matrix& other);
};

}  // namespace s21

#endif  // COMMON_MATRIX_H_
