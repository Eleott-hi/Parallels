#include "program.h"

#include "console.h"

namespace s21 {

void Program::Exec() {
  const Matrix& a = Console::ReadMatrix("A");
  const Matrix& b = Console::ReadMatrix("B");

  if (a.Cols() < 1 || b.Cols() < 1 || a.Cols() != b.Rows()) {
    Console::Error("Incorrect matrix size");
    return;
  }

  int iterations = Console::ReadInt("Enter number of iterations:\n> ");

  if (a.Rows() < 10 && a.Cols() < 10) {
    Console::WriteLine("Matrix A:");
    Console::WriteMatrix(a);
  }
  if (b.Rows() < 10 && b.Cols() < 10) {
    Console::WriteLine("Matrix B:");
    Console::WriteMatrix(b);
  }

  int st_exec_time = ComputeUsingSingleThread(a, b, iterations);
  int pipeline_exec_time = ComputeUsingPipeline(a, b, iterations);
  std::vector<int> mt_exec_times = ComputeUsingMultiThread(a, b, iterations);

  std::stringstream report;
  report << "Single thread execution time = " << st_exec_time << " [ms]\n"
         << "Pipeline execution time = " << pipeline_exec_time << " [ms]\n";

  for (int i = 0; i < mt_exec_times.size(); ++i) {
    report.width(2);
    report << std::to_string(2 * i + 2);
    report << " threads execution time = " << mt_exec_times[i] << " [ms]\n";
  }

  Console::Write(report.str());
}

int Program::ComputeUsingSingleThread(const Matrix& a, const Matrix& b, int n) {
  timer_.Start();

  Matrix matrix(a.Rows(), b.Cols());

  for (int i = 0; i < n; ++i) {
    std::vector<double> row_factor(a.Rows());
    std::vector<double> column_factor(b.Cols());

    Winograd::ComputeRowFactor(row_factor, a, 0, a.Rows());
    Winograd::ComputeColumnFactor(column_factor, b, 0, b.Cols());
    Winograd::ComputeResultMatrix(matrix, 0, b.Cols(), a, b, row_factor,
                                  column_factor);
  }

  int result = timer_.Finish();

  if (matrix.Rows() < 10 && matrix.Cols() < 10) {
    Console::WriteLine("Result #1 (single thread):");
    Console::WriteMatrix(matrix);
  }

  return result;
}

int Program::ComputeUsingPipeline(const Matrix& a, const Matrix& b, int n) {
  timer_.Start();

  Matrix matrix(a.Rows(), b.Cols());
  for (int i = 0; i < n; ++i) {
    Winograd::ComputeMatrixUsingPipeline(matrix, a, b);
  }

  int result = timer_.Finish();

  if (matrix.Rows() < 10 && matrix.Cols() < 10) {
    Console::WriteLine("Result #2 (pipeline):");
    Console::WriteMatrix(matrix);
  }

  return result;
}

std::vector<int> Program::ComputeUsingMultiThread(const Matrix& a,
                                                  const Matrix& b, int n) {
  std::vector<int> result;

  Matrix matrix(a.Rows(), b.Cols());

  const auto processors_amount = std::thread::hardware_concurrency();
  for (int j = 2; j <= processors_amount * 4; j += 2) {
    ThreadPool threads(j);
    int row_step = matrix.Rows() / j;
    int column_step = matrix.Cols() / j;

    timer_.Start();

    // for each iteration (N)
    for (int k = 0; k < n; ++k) {
      std::vector<double> row_factor(a.Rows());
      std::vector<double> column_factor(b.Cols());

      // for each thread get row_factor
      for (int i = 0; i < j; ++i) {
        int begin = i * row_step;
        int end = i != j - 1 ? (i + 1) * row_step : a.Rows();
        threads.AddTask(Winograd::ComputeRowFactor, std::ref(row_factor), a,
                        begin, end);
      }

      // for each thread get column_factor
      for (int i = 0; i < j; ++i) {
        int begin = i * column_step;
        int end = i != j - 1 ? (i + 1) * column_step : b.Cols();
        threads.AddTask(Winograd::ComputeColumnFactor, std::ref(column_factor),
                        b, begin, end);
      }

      // wait for row_factor and column_factor to be computed
      threads.WaitAll();

      auto ComputeMatrix = [&](int begin, int end) {
        Winograd::ComputeResultMatrix(matrix, begin, end, a, b, row_factor,
                                      column_factor);
      };

      // for each thread compute matrix
      for (int i = 0; i < j; ++i) {
        int begin = i * row_step;
        int end = i != j - 1 ? (i + 1) * row_step : a.Rows();
        threads.AddTask(ComputeMatrix, begin, end);
      }

      // wait for matrix to be computed
      threads.WaitAll();
    }

    result.push_back(timer_.Finish());
  }

  if (matrix.Rows() < 10 && matrix.Cols() < 10) {
    Console::WriteLine("Result #3 (multithread):");
    Console::WriteMatrix(matrix);
  }

  return result;
}

}  // namespace s21
