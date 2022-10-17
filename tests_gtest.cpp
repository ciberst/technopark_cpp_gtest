#include <iostream>

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
 public:
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
    array.PushBack(static_cast<double>(i));
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

// disable test
// enable after fix
TEST(Test, DISABLED_Test) {
  EXPECT_TRUE(false);
}

INSTANTIATE_TEST_SUITE_P(All,
                         DArrayTest,
                         ::testing::Values(0ULL, 100ULL, 1000ULL));
INSTANTIATE_TEST_SUITE_P(All5,
                         DArrayTest,
                         ::testing::Values(5ULL, 500ULL, 5000ULL));






class UrlData {
 public:
  UrlData& append(UrlData&&) {
    // impl
    return *this;
  }
};

class URLService {
 public:
  // example.com/test?date=2021-10-28&time=10:12
  UrlData Parse(const std::string& url) {
    // impl
    UrlData result;
    // impl
    result.append(ParseDate(url)).append(ParseTime(url));
    // impl
    return result;
  }

 private:
  // &date=2021-10-28
  UrlData ParseDate(const std::string& url) {
    // impl
    return UrlData(/*impl*/);
  }

  // &time=10:12
  UrlData ParseTime(const std::string& url) {
    // impl
    return UrlData(/*impl*/);
  }
};









namespace utils {
// &date=2021-10-28
UrlData ParseDate(const std::string& url) {
  // impl
  return UrlData(/*impl*/);
}

// &time=10:12
UrlData ParseTime(const std::string& url) {
  // impl
  return UrlData(/*impl*/);
}
}  // namespace utils
