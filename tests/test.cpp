// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <BaseStack.hpp>
#include <NonCopiedStack.hpp>
#include <Stack.hpp>

TEST(Stack, RightClass) {
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
}
TEST(Stack, CopyPush) {
  const int &a = 5, b = 8;
  Stack<int> stack;
  stack.push(a);
  stack.push(b);

  EXPECT_EQ(stack.head(), b);
  stack.pop();
  EXPECT_EQ(stack.head(), a);
  stack.pop();

  EXPECT_THROW(stack.pop(), std::exception);
}
TEST(Stack, MovePush) {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(stack.head(), 2);
  stack.pop();
  EXPECT_EQ(stack.head(), 1);
  stack.pop();
  EXPECT_ANY_THROW(stack.head());
  EXPECT_ANY_THROW(stack.pop());
}
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
TEST(Point, RightClass) {
  EXPECT_TRUE(std::is_move_constructible<Point>::value);
  EXPECT_FALSE(std::is_copy_constructible<Point>::value);
}
class Integer {
 public:
  int value;
  Integer() = default;
  Integer(Integer&& val) = default;
  Integer(const Integer& val) = default;
};
TEST(Integer, RightClass) {
  EXPECT_TRUE(std::is_move_constructible<Integer>::value);
  EXPECT_TRUE(std::is_copy_constructible<Integer>::value);
}

TEST(NonCopiedStack, RightClass) {
  EXPECT_TRUE(std::is_move_constructible<NonCopiedStack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<NonCopiedStack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<NonCopiedStack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<NonCopiedStack<int>>::value);
}
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
  int x1 = 2, y1 = 4;
  int x2 = 3, y2 = 7;
  Point pnt(x1, y1);

  NonCopiedStack<Point> stack;
  stack.push(Point(x1, y1));
  stack.push_emplace(x2, y2);
  EXPECT_EQ(stack.head().x, x2);
  stack.pop();
  EXPECT_EQ(stack.head().y, y1);
  stack.pop();
  EXPECT_ANY_THROW(stack.pop());
  stack.push(Point(x1, y1));
}
