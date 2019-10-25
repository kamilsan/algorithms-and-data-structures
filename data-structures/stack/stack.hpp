#pragma once

#include "../linked-list/linkedList.hpp"

template <typename T>
class Stack
{
public:
  Stack() = default;

  T pop();
  void push(const T& item);

  const T& peek() const noexcept;
  size_t size() const noexcept;
  bool isEmpty() const noexcept;
private:
  LinkedList<T> list_;
};

template <typename T>
T Stack<T>::pop()
{
  return list_.remove_front();
}

template <typename T>
void Stack<T>::push(const T& item)
{
  list_.add_front(item);
}

template <typename T>
const T& Stack<T>::peek() const noexcept
{
  return list_.get_front();
}

template <typename T>
size_t Stack<T>::size() const noexcept
{
  return list_.size();
}

template <typename T>
bool Stack<T>::isEmpty() const noexcept
{
  return list_.isEmpty();
}
