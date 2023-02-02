#include "matrix.h"

namespace s21 {

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) { Init(); }

Matrix::~Matrix() { delete[] data_; }

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  Init();
  Copy(other);
}

Matrix::Matrix(Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
  other.cols_ = 0;
  other.rows_ = 0;
  other.data_ = nullptr;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (&other != this) {
    delete[] data_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    Init();
    Copy(other);
  }

  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) {
  if (&other != this) {
    delete[] data_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = other.data_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
  }

  return *this;
}

double Matrix::operator()(int row, int col) const {
  return data_[row * cols_ + col];
}

double& Matrix::operator()(int row, int col) {
  return data_[row * cols_ + col];
}

void Matrix::FillRandomly(int from, int to) {
  for (int i = 0; i < rows_ * cols_; ++i) {
    data_[i] = static_cast<double>(Random(from, to));
  }
}

void Matrix::Init() {
  if (rows_ > 0 && cols_ > 0) data_ = new double[rows_ * cols_]{0};
}

void Matrix::Copy(const Matrix& other) {
  for (int i = 0; i < rows_ * cols_; ++i) {
    data_[i] = other.data_[i];
  }
}

}  // namespace s21
