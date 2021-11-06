// Copyright by C-developers1488

#ifndef INCLUDE_PTR_HPP_
#define INCLUDE_PTR_HPP_

#include <atomic>
#include <cstdio>
#include <utility>


template <typename T>
class SharedPtr {
  T* ObPtr;
  std::atomic_uint* count;

 public:
  SharedPtr();
  SharedPtr(T *ptr);
  SharedPtr(const SharedPtr& r);
  SharedPtr(SharedPtr&& r);
  ~SharedPtr();

  SharedPtr<T> operator=(const SharedPtr& r);
  SharedPtr<T>& operator=(SharedPtr&& r);

  operator bool() const;
  T& operator*() const;

  T* operator->() const;

  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPtr& r);

  auto use_count() const -> size_t;
};

template <typename T>
SharedPtr<T>::SharedPtr() {
  ObPtr = nullptr;
  count = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T *ptr) {
  ObPtr = ptr;
  count = new std::atomic_uint(1);
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &r) {
  ObPtr = r.ObPtr;
  count = r.count;
  (*count)++;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr &&r)
{
  ObPtr = r.ObPtr;
  count = r.count;
  r.ObPtr = nullptr;
  r.count = nullptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr()

{
  if (count) {
    if (*count == 1) {
      delete count;
      delete ObPtr;
    } else
      (*count)--;
  }
}

template <typename T>
SharedPtr<T> SharedPtr<T>::operator=(const SharedPtr &r) {
  ObPtr = r.ObPtr;
  count = r.count;
  *count++;
  return *this;
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr &&r) {
  ObPtr = r.ObPtr;
  count = r.count;
  r.ObPtr = nullptr;
  r.count = nullptr;
  return *this;
}

template <typename T>
SharedPtr<T>::operator bool() const {
  return ObPtr != nullptr;
}

template <typename T>
T &SharedPtr<T>::operator*() const {
  return *ObPtr;
}

template <typename T>
T *SharedPtr<T>::operator->() const {
  return ObPtr;
}

template <typename T>
auto SharedPtr<T>::get() -> T * {
  return ObPtr;
}

template <typename T>
void SharedPtr<T>::reset() {
  *this = SharedPtr();
}

template <typename T>
void SharedPtr<T>::reset(T *ptr) {
  *this = SharedPtr(ptr);
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr &r) {
  std::swap(ObPtr, r.ObPtr);
  std::swap(count, r.count);
}

template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  return (*count);
}

#endif // INCLUDE_PTR_HPP_