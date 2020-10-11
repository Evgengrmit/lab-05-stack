// Copyright 2020 Evgeniy Grigorev <your_email>

#ifndef INCLUDE_STACK_HPP_
#define INCLUDE_STACK_HPP_

#include "BaseStack.hpp"

template <typename T>
class Stack : public BaseStack<T> {
 public:
  using BS = BaseStack<T>;
  void push(const T &value);
  void pop();
};

template <typename T>
void Stack<T>::push(const T &value) {
  auto *current = new Element<T>{value, BS::head_};
  BaseStack<T>::head_ = current;
}

template <typename T>
void Stack<T>::pop() {
  if (BS::head_) {
    auto *upper = BS::head_;
    BS::head_ = BS::head_->previous;
    delete upper;
  } else {
    throw std::out_of_range("Empty Stack!!!");
  }
}

#endif  // INCLUDE_STACK_HPP_
