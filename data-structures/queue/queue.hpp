#pragma once

#include "../doubly-linked-list/doublyLinkedList.hpp"

template <typename T>
class Queue
{
public:
  Queue() = default;

  T front();
  T back();
  T dequeue();
  void enqueue(const T& item);

  const T& front() const noexcept;
  const T& back() const noexcept;
  size_t size() const noexcept;
  bool isEmpty() const noexcept;
private:
  DoublyLinkedList<T> list_;
};

template <typename T>
T Queue<T>::front()
{
  return list_.get_front();
}

template <typename T>
T Queue<T>::back()
{
  return list_.get_back();
}

template <typename T>
T Queue<T>::dequeue()
{
  return list_.remove_front();
}

template <typename T>
void Queue<T>::enqueue(const T& item)
{
  list_.add_back(item);
}

template <typename T>
const T& Queue<T>::front() const noexcept
{
  return list_.get_front();
}

template <typename T>
const T& Queue<T>::back() const noexcept
{
  return list_.get_back();
}

template <typename T>
size_t Queue<T>::size() const noexcept
{
  return list_.size();
}

template <typename T>
bool Queue<T>::isEmpty() const noexcept
{
  return list_.isEmpty();
}