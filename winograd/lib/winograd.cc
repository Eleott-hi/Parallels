#include "winograd.h"

namespace s21 {

void Winograd::ComputeRowFactor(std::vector<double>& result,
                                const Matrix& matrix, int begin, int end) {
  for (int i = begin; i < end; ++i)
    for (int j = 0; j < matrix.Cols() / 2; ++j)
      result[i] += matrix(i, 2 * j) * matrix(i, 2 * j + 1);
}

void Winograd::ComputeColumnFactor(std::vector<double>& result,
                                   const Matrix& matrix, int begin, int end) {
  for (int i = begin; i < end; ++i)
    for (int j = 0; j < matrix.Rows() / 2; ++j)
      result[i] += matrix(2 * j, i) * matrix(2 * j + 1, i);
}

void Winograd::ComputeResultMatrix(Matrix& result, int begin, int end,
                                   const Matrix& a, const Matrix& b,
                                   const std::vector<double>& row_factor,
                                   const std::vector<double>& column_factor) {
  for (int i = begin; i < end; ++i) {
    for (int j = 0; j < b.Cols(); ++j) {
      result(i, j) = -row_factor[i] - column_factor[j];

      for (int k = 0; k < a.Cols() / 2; ++k)
        result(i, j) +=
            (a(i, 2 * k) + b(2 * k + 1, j)) * (a(i, 2 * k + 1) + b(2 * k, j));
    }
  }

  if (a.Cols() % 2 != 0)
    for (int i = begin; i < end; ++i)
      for (int j = 0; j < b.Cols(); ++j)
        result(i, j) += a(i, a.Cols() - 1) * b(a.Cols() - 1, j);
}

void Winograd::ComputeMatrixUsingPipeline(Matrix& result, const Matrix& a,
                                          const Matrix& b) {
  std::vector<std::mutex> mutexes(a.Rows() * b.Cols());
  std::queue<std::pair<int, double>> row_factors;
  std::queue<std::pair<int, double>> col_factors;
  std::mutex mtx_row_factor;
  std::mutex mtx_col_factor;
  std::atomic_bool stop_row_factor = false;
  std::atomic_bool stop_col_factor = false;

  result = Matrix(a.Rows(), b.Cols());

  ThreadPool threads(2);
  ThreadPool pipeline(4);

  threads.AddTask([&] { CalcRemain(result, a, b, mutexes); });
  threads.AddTask([&] { CalcMain(result, a, b, mutexes); });

  pipeline.AddTask([&] {
    for (int i = 0; i < a.Rows(); ++i) {
      double factor = 0;

      for (int j = 0; j < a.Cols() / 2; ++j)
        factor += a(i, 2 * j) * a(i, 2 * j + 1);

      std::scoped_lock<std::mutex> lock(mtx_row_factor);
      row_factors.emplace(i, factor);
    }
    stop_row_factor = true;
  });

  pipeline.AddTask([&] {
    for (int i = 0; i < b.Cols(); ++i) {
      double factor = 0;

      for (int j = 0; j < b.Rows() / 2; ++j)
        factor += b(2 * j, i) * b(2 * j + 1, i);

      std::scoped_lock<std::mutex> lock(mtx_col_factor);
      col_factors.emplace(i, factor);
    }
    stop_col_factor = true;
  });

  pipeline.AddTask([&] {
    std::pair<int, double> row_factor;
    while (true) {
      {
        std::scoped_lock<std::mutex> lock(mtx_row_factor);
        if (row_factors.empty()) {
          if (stop_row_factor) {
            return;
          } else {
            continue;
          }
        }

        row_factor = row_factors.front();
        row_factors.pop();
      }

      for (int j = 0; j < result.Cols(); ++j) {
        std::scoped_lock<std::mutex> lock(
            mutexes.at(row_factor.first * result.Cols() + j));
        result(row_factor.first, j) -= row_factor.second;
      }
    }
  });

  pipeline.AddTask([&] {
    std::pair<int, double> col_factor;
    while (true) {
      {
        std::scoped_lock<std::mutex> lock(mtx_col_factor);
        if (col_factors.empty()) {
          if (stop_col_factor) {
            return;
          } else {
            continue;
          }
        }

        col_factor = col_factors.front();
        col_factors.pop();
      }

      for (int i = 0; i < result.Rows(); ++i) {
        std::scoped_lock<std::mutex> lock(
            mutexes.at(i * result.Cols() + col_factor.first));
        result(i, col_factor.first) -= col_factor.second;
      }
    }
  });

  pipeline.WaitAll();
  threads.WaitAll();
}

void Winograd::CalcRemain(Matrix& result, const Matrix& a, const Matrix& b,
                          std::vector<std::mutex>& mutexes) {
  if (a.Cols() % 2 != 0) {
    for (int i = 0; i < result.Rows(); ++i) {
      for (int j = 0; j < result.Cols(); ++j) {
        std::scoped_lock<std::mutex> lock(mutexes.at(i * result.Cols() + j));
        result(i, j) += a(i, a.Cols() - 1) * b(a.Cols() - 1, j);
      }
    }
  }
}

void Winograd::CalcMain(Matrix& result, const Matrix& a, const Matrix& b,
                        std::vector<std::mutex>& mutexes) {
  for (int i = 0; i < result.Rows(); ++i) {
    for (int j = 0; j < result.Cols(); ++j) {
      std::scoped_lock<std::mutex> lock(mutexes.at(i * result.Cols() + j));
      for (int k = 0; k < a.Cols() / 2; ++k)
        result(i, j) +=
            (a(i, 2 * k) + b(2 * k + 1, j)) * (a(i, 2 * k + 1) + b(2 * k, j));
    }
  }
}

}  // namespace s21
