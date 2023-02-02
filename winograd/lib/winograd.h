#ifndef A3_SRC_WINOGRAD_LIB_WINOGRAD_H_
#define A3_SRC_WINOGRAD_LIB_WINOGRAD_H_

#include "matrix.h"
#include "thread_pool.h"

namespace s21 {

class Winograd {
 public:
  static void ComputeRowFactor(std::vector<double>&, const Matrix&, int begin,
                               int end);
  static void ComputeColumnFactor(std::vector<double>&, const Matrix&,
                                  int begin, int end);
  static void ComputeResultMatrix(Matrix& result, int begin, int end,
                                  const Matrix& a, const Matrix& b,
                                  const std::vector<double>& row_factor,
                                  const std::vector<double>& column_factor);
  static void ComputeMatrixUsingPipeline(Matrix& result, const Matrix& a,
                                         const Matrix& b);

 private:
  static void CalcRemain(Matrix& result, const Matrix& a, const Matrix& b,
                         std::vector<std::mutex>& mutexes);
  static void CalcMain(Matrix& result, const Matrix& a, const Matrix& b,
                       std::vector<std::mutex>& mutexes);
};

}  // namespace s21

#endif  // A3_SRC_WINOGRAD_LIB_WINOGRAD_H_
