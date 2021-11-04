// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_SHARED_PTR_HPP_
#define INCLUDE_SHARED_PTR_HPP_

#include <iostream>

class shared_ptr {
public:
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(shared_ptr<T>& other);
    shared_ptr<T> operator= (shared_ptr<T>& other);
    ~shared_ptr();
    size_t use_count() const;
    bool unique() const;
private:
    T* ptr;
    size_t *count;
};



#endif // INCLUDE_SHARED_PTR_HPP_
