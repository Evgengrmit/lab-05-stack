// Copyright 2020 Evgeniy Grigorev <your_email>

#include <gtest/gtest.h>

#include <BaseStack.hpp>
#include <NonCopiedStack.hpp>
#include <Stack.hpp>

// TEST CLASSES
class Point {
 public:
  int x;
  int y;
  Point() = default;
  Point(int x1, int y1) : x(x1), y(y1) {}
  Point(Point&& value) noexcept = default;
  Point(const Point& value) = delete;
  auto operator=(Point&& value) noexcept -> Point& = default;
  auto operator=(const Point& value) -> Point& = delete;
};

class Integer {
 public:
  int value;
  Integer() = default;
  Integer(Integer&& val) = default;
  Integer(const Integer& val) = default;
};
//  Check tests classes
TEST(Point, RightClass) {
  EXPECT_TRUE(std::is_move_constructible<Point>::value);
  EXPECT_FALSE(std::is_copy_constructible<Point>::value);
}

TEST(Integer, RightClass) {
  EXPECT_TRUE(std::is_move_constructible<Integer>::value);
  EXPECT_TRUE(std::is_copy_constructible<Integer>::value);
}
// Check Stack classes
TEST(Stack, MovableClass) {
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
}
TEST(Stack, NonCopyedClass) {
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
}

TEST(NonCopiedStack, MovableClass) {
  EXPECT_TRUE(std::is_move_constructible<NonCopiedStack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<NonCopiedStack<int>>::value);
}

TEST(NonCopiedStack, NonCopyedClass) {
  EXPECT_FALSE(std::is_copy_constructible<NonCopiedStack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<NonCopiedStack<int>>::value);
}
//Check methods class Stack
TEST(Stack, CopyPush) {
  Stack<int> stack;
  stack.push(static_cast<const int&>(5));
  stack.push(static_cast<const int&>(8));
  EXPECT_EQ(stack.head(), 8);
  stack.pop();
  EXPECT_EQ(stack.head(), 5);
}

TEST(Stack, Pop) {
  Stack<int> stack;
  EXPECT_ANY_THROW(stack.pop());
}

TEST(Stack, MovePush) {
  Stack<int> stack;
  stack.push(1);
  EXPECT_EQ(stack.head(), 1);
}

TEST(Stack, Head) {
  Stack<int> stack;
  EXPECT_ANY_THROW(stack.head());
}
//Check methods class NonCopiedStack
TEST(NonCopiedStack, ErorrMovePush) {
  NonCopiedStack<Integer> stack;
  Integer x{};
  x.value = 1;
  EXPECT_ANY_THROW(stack.push(std::move(x)));
}

TEST(NonCopiedStack, MovePush) {
  NonCopiedStack<Point> stack;
  Point p{1, 2};
  stack.push(std::move(p));
  Point p1{stack.pop()};
  EXPECT_EQ(p1.x, 1);
  EXPECT_EQ(p1.y, 2);
}

TEST(NonCopiedStack, AddElement) {
  NonCopiedStack<Point> stack;
  stack.push(Point(2, 4));
  stack.push_emplace(3, 7);
  EXPECT_EQ(stack.head().x, 3);
  stack.pop();
  EXPECT_EQ(stack.head().y, 4);
}

TEST(NonCopiedStack, Pop) {
  NonCopiedStack<Point> stack;
  EXPECT_ANY_THROW(stack.pop());
}
