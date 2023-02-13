#ifndef COMMON_TIMER_H_
#define COMMON_TIMER_H_

#include <chrono>

#include "console.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;

namespace s21 {

class Timer {
 public:
  void Start() { timestamp_ = GetTime(); }

  int Finish() {
    return duration_cast<milliseconds>(GetTime() - timestamp_).count();
  }

 private:
  using Timestamp = std::chrono::high_resolution_clock::time_point;

  Timestamp timestamp_ = GetTime();

  Timestamp GetTime() { return std::chrono::high_resolution_clock::now(); }
};

}  // namespace s21

#endif  // COMMON_TIMER_H_
