// Copyright by seyjez
#ifndef INCLUDE_PTR_HPP_
#define INCLUDE_PTR_HPP_

#include <stdexcept>
#include <atomic>
#include <vector>
#include <iostream>
#include <utility>

auto example() -> void;

template <typename T>
class SharedPtr {
 public:
  SharedPtr(){
    ptr = nullptr;
    counter = new std::atomic_uint;
    *this->counter = 0;
  }

  explicit SharedPtr(T* pointer){
    counter = new std::atomic_uint;
    ptr = pointer;
    *this->counter = 1;
  }

  SharedPtr(const SharedPtr& r){
    ptr = r.ptr;
    counter = r.counter;
    (*this->counter)++;
  }

  SharedPtr(SharedPtr&& r){
    ptr = std::move(r.ptr);
    counter = std::move(r.counter);
  }

  ~SharedPtr(){
    if ((*this->counter) < 2)
    {
      delete counter;
    } else {
      ptr = nullptr;
      (*this->counter)--;
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr&{
    if ((*this->counter) > 1)
    {
      (*this->counter)--;
    }
    ptr = r.ptr;
    counter = r.counter;
    (*this->counter)++;
    return *this;
  }

  auto operator=(SharedPtr&& r) -> SharedPtr&{
    if ((*this->counter) > 1)
    {
      (*this->counter)--;
    }
    ptr = std::move(r.ptr);
    counter = std::move(r.counter);
    return *this;
  }

  operator bool() const{
    return (ptr != nullptr);
  }

  auto operator*() const -> T&{
    return (*this->ptr);
  }

  auto operator->() const -> T*{
    return ptr;
  }

  auto get() -> T*{
    return ptr;
  }

  void reset(){
    if (*this->counter > 1)
    {
      (*this->counter)--;
    } else {
      delete counter;
    }
    ptr = nullptr;
    counter = new std::atomic_uint;
    *this->counter = 0;
  }

  void reset(T* pointer){
    if (*this->counter > 1)
    {
      (*this->counter)--;
    } else {
      delete this->counter;
    }
    ptr = pointer;
    counter = new std::atomic_uint;
    *this->counter = 1;
  }

  void swapPtr(SharedPtr& r){
    T* temp1 = ptr;
    std::atomic_uint* temp2 = counter;
    ptr = r.ptr;
    counter = r.counter;
    r.ptr = temp1;
    r.counter = temp2;
  }

  auto use_count() const -> size_t{
    if (counter == nullptr)
    {
      return 0;
    } else {
      return *this->counter;
    }
  }

 private:
  T* ptr;
  std::atomic_uint* counter;
};

#endif // INCLUDE_PTR_HPP_

