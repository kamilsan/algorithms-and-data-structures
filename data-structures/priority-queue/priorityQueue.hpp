#pragma once

#include "../heap/heap.hpp"

template <typename T, typename C = std::less<T>>
class PriorityQueue
{
public:
  PriorityQueue(int capacity);
  PriorityQueue() : PriorityQueue(4) {}

  T dequeue();
  void enqueue(const T& item);

  const T& peek() const noexcept;
  size_t size() const noexcept;
  bool isEmpty() const noexcept;
private:
  Heap<T, C> heap_;
};

template <typename T, typename C>
PriorityQueue<T, C>::PriorityQueue(int capacity): heap_(capacity) {}

template <typename T, typename C>
T PriorityQueue<T, C>::dequeue()
{
  return heap_.pop();
}

template <typename T, typename C>
void PriorityQueue<T, C>::enqueue(const T& item)
{
  heap_.insert(item);
}

template <typename T, typename C>
const T& PriorityQueue<T, C>::peek() const noexcept
{
  return heap_.peek();
}

template <typename T, typename C>
size_t PriorityQueue<T, C>::size() const noexcept
{
  return heap_.size();
}

template <typename T, typename C>
bool PriorityQueue<T, C>::isEmpty() const noexcept
{
  return heap_.isEmpty();
}
