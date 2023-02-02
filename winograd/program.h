#ifndef A3_SRC_WINOGRAD_PROGRAM_H_
#define A3_SRC_WINOGRAD_PROGRAM_H_

#include <chrono>  // std::chrono

#include "lib/winograd.h"
#include "timer.h"

namespace s21 {

class Program {
 public:
  void Exec();

 private:
  int ComputeUsingSingleThread(const Matrix&, const Matrix&, int);
  int ComputeUsingPipeline(const Matrix&, const Matrix&, int);
  std::vector<int> ComputeUsingMultiThread(const Matrix&, const Matrix&, int);

  Timer timer_;
};

}  // namespace s21

#endif  // A3_SRC_WINOGRAD_PROGRAM_H_
