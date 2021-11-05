// Copyright 2019 DenisSlack

#include <gtest/gtest.h>

#include "ptr.hpp"


TEST(SharedPtr_Test, TestOne) {
  int* p = new int{2};
  SharedPtr<int> ptr1(p);
  EXPECT_EQ(*ptr1.get(), 2);
  EXPECT_EQ(ptr1.get(), p);
}

TEST(SharedPtr_Test, TestTwo) {
  int* p1 = new int{3};
  int* p2 = new int{2};

  SharedPtr<int> ptr1(p1);
  SharedPtr<int> ptr2(p2);
  ptr2.swap(ptr1);
  EXPECT_EQ(*ptr2.get(), 3);
  EXPECT_EQ(*ptr1.get(), 2);
}

TEST(SharedPtr_Test, TestThree) {
  int* p = new int{5};

  SharedPtr<int> ptr1(p);

  ptr1.reset(p);
  EXPECT_EQ(ptr1.get(), p);

  ptr1.reset();
  EXPECT_EQ(ptr1.get(), nullptr);
}
