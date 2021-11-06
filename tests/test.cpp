// Copyright by C-developers1488


#include <gtest/gtest.h>
#include <stdexcept>

#include "ptr.hpp"

TEST(ptrTest, nullPtrTest) {
  SharedPtr<size_t> a;
  ASSERT_EQ(a.use_count(), 0);
}

TEST(ptrTest, swapPtrTest) {
  struct Widget {
    size_t in;
    size_t out;
  };
  Widget widget1 = { 1, 2 };
  Widget widget2 = { 2, 1 };
  SharedPtr<Widget> a(&widget1);
  SharedPtr<Widget> b(&widget2);
  a.swapPtr(b);
  ASSERT_EQ(a.get(), &widget2);
}

TEST(ptrTest, resetPtrTest) {
  struct Widget {
    size_t in;
    size_t out;
  };
  Widget widget = { 1, 2 };
  SharedPtr<Widget> a(&widget);
  a.reset();
  ASSERT_EQ(a.use_count(), 0);
}

TEST(ptrTest, objectPtrTest) {
  struct Widget {
    size_t in;
    size_t out;
  };
  Widget widget = { 0, 0 };
  SharedPtr<Widget> a(&widget);
  ASSERT_EQ(a.get(), &widget);
}

TEST(ptrTest, sharedPtrTest) {
  size_t in = 10;
  SharedPtr<size_t> a(&in);
  SharedPtr<size_t> b(a);
  SharedPtr<size_t> c(b);
  ASSERT_EQ(c.use_count(), 3);
}