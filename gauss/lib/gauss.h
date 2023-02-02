#ifndef A3_SRC_GAUSS_LIB_GAUSS_H_
#define A3_SRC_GAUSS_LIB_GAUSS_H_

#include "barrier.h"
#include "matrix.h"
#include "thread_pool.h"

namespace s21 {

class Gauss {
 public:
  static std::vector<double> SolveOneThread(Matrix matrix);

  static std::vector<double> SolveMultiThread(  //
      Matrix matrix,                            //
      int thread_num = (int)std::thread::hardware_concurrency());

 private:
  static void FeedForward(Matrix &matrix,  //
                          int start,       //
                          int end,         //
                          Barrier &barrier);

  static void FeedBackward(Matrix &matrix,  //
                           int start,       //
                           int end,         //
                           Barrier &barrier);
};

}  // namespace s21

#endif  // A3_SRC_GAUSS_LIB_GAUSS_H_
