// Copyright by C-developers1488

#ifndef INCLUDE_PTR_HPP_
#define INCLUDE_PTR_HPP_

#include <stdexcept>
#include <atomic>
#include <vector>
#include <iostream>

auto example() -> void;

template <typename T>
class SharedPtr {
  T* ptr;
  std::atomic_uint* counter;
 public:
  SharedPtr();
  explicit SharedPtr(T* pointer);
  SharedPtr(const SharedPtr& r);
  SharedPtr(SharedPtr&& r);
  ~SharedPtr();
  auto operator=(const SharedPtr& r) -> SharedPtr&;
  auto operator=(SharedPtr&& r) -> SharedPtr&;
  operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;
  auto get() -> T*;

  void reset(){
    if (*this->counter > 1)
    {
      (*this->counter)--;
    } else {
      delete this->counter;
    }
    this->ptr = nullptr;
    this->counter = new std::atomic_uint;
    *this->counter = 0;
  }

  void reset(T* pointer){
    if (*this->counter > 1)
    {
      (*this->counter)--;
    } else {
      delete this->counter;
    }
    this->ptr = pointer;
    this->counter = new std::atomic_uint;
    *this->counter = 1;
  }

  void swapPtr(SharedPtr& r){
    T* temp1 = this->ptr;
    std::atomic_uint* temp2 = this->counter;
    this->ptr = r.ptr;
    this->counter = r.counter;
    r.ptr = temp1;
    r.counter = temp2;
  }
  auto use_count() const -> size_t;
};

template <typename T>
SharedPtr<T>::SharedPtr(){
  this->ptr = nullptr;
  this->counter = new std::atomic_uint;
  *this->counter = 0;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* pointer){
  this->counter = new std::atomic_uint;
  this->ptr = pointer;
  *this->counter = 1;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& r){
  this->ptr = r.ptr;
  this->counter = r.counter;
  (*this->counter)++;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& r){
  this->ptr = r.ptr;
  this->counter = r.counter;
  r.ptr = nullptr;
  delete r.counter;
}

template <typename T>
SharedPtr<T>::~SharedPtr(){
  if ((*this->counter) < 2)
  {
    delete this->counter;
  } else {
    this->ptr = nullptr;
    (*this->counter)--;
  }
}

template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr& r) -> SharedPtr&{
  if ((*this->counter) > 1)
  {
    (*this->counter)--;
  }
  this->ptr = r.ptr;
  this->counter = r.counter;
  (*this->counter)++;
  return *this;
}

template <typename T>
auto SharedPtr<T>::operator=(SharedPtr&& r) -> SharedPtr&{
  if ((*this->counter) > 1)
  {
    (*this->counter)--;
  }
  this->ptr = r.ptr;
  this->counter = r.counter;
  delete r.counter;
  return *this;
}

template <typename T>
SharedPtr<T>::operator bool() const{
  return (this->ptr != nullptr);
}

template <typename T>
auto SharedPtr<T>::operator*() const -> T&{
  return (*this->ptr);
}

template <typename T>
auto SharedPtr<T>::operator->() const -> T*{
  return this->ptr;
}

template<typename T>
auto SharedPtr<T>:: get() -> T*{
  return this->ptr;
}

template <typename T>
auto SharedPtr<T>::use_count() const -> size_t{
  if (this->counter == nullptr)
  {
    return 0;
  } else {
    return *this->counter;
  }
}

#endif // INCLUDE_PTR_HPP_
