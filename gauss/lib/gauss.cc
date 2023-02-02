#include "gauss.h"

namespace s21 {

std::vector<double> Gauss::SolveOneThread(Matrix matrix) {
  int rows = matrix.Rows();
  std::vector<double> res(rows, 0);

  // FeedForward
  for (int k = 0; k < rows - 1; ++k)
    for (int i = k + 1; i < rows; ++i) {
      double ratio = matrix(i, k) / matrix(k, k);

      for (int j = 1; j < matrix.Cols(); ++j)
        matrix(i, j) -= ratio * matrix(k, j);
    }

  // FeedBackward
  for (int i = rows - 1; i > -1; --i) {
    res[i] = matrix(i, rows);
    for (int j = i + 1; j < rows; ++j) {
      res[i] -= matrix(i, j) * res[j];
    }
    res[i] /= matrix(i, i);
  }

  return res;
}

std::vector<double> Gauss::SolveMultiThread(Matrix matrix, int thread_num) {
  if (thread_num > matrix.Rows()) thread_num = matrix.Rows();

  ThreadPool pool(thread_num);
  Barrier bar(thread_num), phase(thread_num);

  auto func = [&matrix, &bar, &phase](int start, int end) {
    FeedForward(matrix, start, end, bar);

    if (end == matrix.Rows()) matrix(end - 1, end) /= matrix(end - 1, end - 1);
    phase.Wait();

    FeedBackward(matrix, start, end, bar);
  };

  int step = matrix.Rows() / thread_num;

  for (int i = 0; i < thread_num; ++i) {
    int start = i * step;
    int end = (i + 1) * step;

    pool.AddTask(func, start, (i == thread_num - 1) ? matrix.Rows() : end);
  }

  pool.WaitAll();

  std::vector<double> answers;
  answers.reserve(matrix.Rows());

  for (int i = 0; i < matrix.Rows(); ++i)
    answers.push_back(matrix(i, matrix.Rows()));

  return answers;
}

void Gauss::FeedForward(Matrix &matrix, int start, int end, Barrier &barrier) {
  int rows = matrix.Rows();
  int cols = matrix.Cols();

  for (int k = 0; k < rows - 1; ++k) {
    for (int i = k + 1; i < rows; ++i) {
      if ((i >= start) && (i < end)) {
        double ratio = matrix(i, k) / matrix(k, k);
        for (int j = 1; j < cols; ++j) matrix(i, j) -= ratio * matrix(k, j);
      }
    }
    barrier.Wait();
  }
}

void Gauss::FeedBackward(Matrix &matrix, int start, int end, Barrier &barrier) {
  int rows = matrix.Rows();
  for (int i = rows - 2; i > -1; --i) {
    if ((i >= start) && (i < end)) {
      for (int j = i + 1; j < rows; ++j)
        matrix(i, rows) -= matrix(i, j) * matrix(j, rows);
      matrix(i, rows) /= matrix(i, i);
    }
    barrier.Wait();
  }
}

}  // namespace s21
