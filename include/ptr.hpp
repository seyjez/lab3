// Copyright by C-developers1488

#include <atomic>
#include <cstdio>


template <typename T>
class SharedPtr {
  T* ObPtr;
  std::atomic_uint* count;

 public:
  SharedPtr();
  SharedPtr(T* ptr);
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

