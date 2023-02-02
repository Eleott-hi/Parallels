#include "barrier.h"

namespace s21 {

void Barrier::Wait() {
  std::unique_lock<std::mutex> lock{mtx_};
  int l_gen = generation_;
  if (!--count_) {
    ++generation_;
    count_ = threshold_;
    cond_.notify_all();
  } else {
    while (l_gen == generation_)  // spurious awake protection
      cond_.wait(lock, [this, l_gen] { return l_gen != generation_; });
  }
}

}  // namespace s21
