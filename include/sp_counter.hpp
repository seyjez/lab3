// Copyright by C-developers1488

#ifndef  INCLUDE_SPCOUNTER_HPP_
#define INCLUDE_SPCOUNTER_HPP_

#include "ptr.hpp"

template<typename T>
class SPCounter {
 public:
  SPCounter(T* p) noexcept{
    count = 1;
    ptr = p;
  }
  void add() noexcept { ++count; }
  void release() noexcept {
    if (!--count) {
      ptr = nullptr;
      delete this;
    }
  }
  auto use_count() const noexcept -> size_t { return count.load(); }
  void unadd(){count--;}
  void add(size_t c){
    count = c;
  }
 private:
  std::atomic<size_t> count;
  T* ptr;
};

#endif //  INCLUDE_SPCOUNTER_HPP_