#include <iostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "DArray.h"
#include "Heap.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"

TEST(DArrayTest, SizeCapacity) {
  DArray darray(64);
  darray.PushBack(5);
  ASSERT_EQ(darray.Size(), 1);
  // ..
  EXPECT_EQ(darray.Capacity(), 64);
}

TEST(DArrayTest, PopBack) {
  DArray darray(64);

  darray.PushBack(5);
  darray.PushBack(5);
  darray.PushBack(5);
  darray.PushBack(5);

  ASSERT_NO_THROW(darray.PopBack());
  ASSERT_NO_THROW(darray.PopBack());
  ASSERT_NO_THROW(darray.PopBack());
  ASSERT_NO_THROW(darray.PopBack());
  EXPECT_THROW(darray.PopBack(), std::runtime_error);
}

TEST(QueueTest, Pop) {
  Queue queue(5);

  EXPECT_NO_THROW(queue.Push(5));
  EXPECT_NO_THROW(queue.Pop());
  EXPECT_NO_THROW(queue.Push(10));
  EXPECT_NO_THROW(queue.Push(20));  // queue contains only 20

  EXPECT_EQ(queue.Front(), 10) << "Queue Front should be 10";
  EXPECT_EQ(queue.Back(), 20) << "Queue Back should be 20";

  EXPECT_NO_THROW(queue.Push(40));  // queue contains 10 20 40
  EXPECT_NO_THROW(queue.Push(60));  // queue contains 20 40 60
  EXPECT_NO_THROW(queue.Pop());
  EXPECT_NO_THROW(queue.Push(80));  // queue contains 40 60 80

  EXPECT_EQ(queue.Back(), 80) << "Queue Front should be 80";
}

class ArrayTest : public ::testing::Test {
 protected:
  void SetUp() override {
    std::cerr << "ArrayTest::SetUp()" << std::endl;
    a0_.PushBack(1);
    a0_.PushBack(2);
    a0_.PushBack(3);
  }

  void TearDown() override {
    std::cerr << "ArrayTest::TearDown()" << std::endl;
  }

  DArray a0_;
};

TEST_F(ArrayTest, IsNotEmptyInitiallySize) {
  EXPECT_EQ(a0_.Size(), 3);
}

TEST_F(ArrayTest, IsNotEmptyInitiallyCapacity) {
  EXPECT_EQ(a0_.Capacity(), 10);
}

class DArrayTest : public ::testing::TestWithParam<size_t> {};

TEST_P(DArrayTest, Capacity) {
  DArray array(GetParam());
  EXPECT_EQ(array.Size(), 0);
  EXPECT_TRUE(array.IsEmpty());
  EXPECT_EQ(array.Capacity(), GetParam());
}

TEST_P(DArrayTest, Size) {
  const size_t count = GetParam();
  DArray array;
  for (size_t i = 0; i < count; ++i) {
    array.PushBack(i);
  }
  EXPECT_EQ(array.Size(), count);

  if (count != 0)
    EXPECT_FALSE(array.IsEmpty());
  else
    EXPECT_TRUE(array.IsEmpty());

  for (size_t i = 0; i < count; ++i) {
    EXPECT_EQ(array.Size(), count - i);
    array.PopBack();
  }
  EXPECT_EQ(array.Size(), 0);
  EXPECT_TRUE(array.IsEmpty());
}

INSTANTIATE_TEST_SUITE_P(All,
                         DArrayTest,
                         ::testing::Values(0ULL, 100ULL, 1000ULL));