#include <iostream>

#include "heap.hpp"

template <typename T, typename C>
void printHeap(const Heap<T, C>& heap)
{
  for(size_t i = 0; i < heap.size(); ++i)
  {
    std::cout << heap[i];
    if(i != heap.size() - 1) std::cout << ", ";
  }
  std::cout << std::endl;
}

int main()
{
  Heap<int, std::greater<int>> heap;
  heap.insert(43);
  heap.insert(15);
  heap.insert(8);
  heap.insert(10);
  heap.insert(12);
  heap.insert(1);
  heap.insert(2);
  heap.insert(9);
  heap.insert(10);
  printHeap(heap);
  std::cout << "Size: " << heap.size() << ", capacity: " << heap.capacity() << std::endl;
  std::cout << "Peek: " << heap.peek() << std::endl;

  std::cout << "Pop..." << std::endl;
  heap.pop();
  printHeap(heap);

  heap.contains(5) ? std::cout << "Heap contains 5." : std::cout << "Heap does not contain 5.";
  std::cout << std::endl;
  heap.contains(12) ? std::cout << "Heap contains 12." : std::cout << "Heap does not contain 12.";
  std::cout << std::endl;

  std::cout << "Peek: " << heap.peek() << std::endl;

  std::cout << "Remove 2" << std::endl;
  heap.remove(2);
  printHeap(heap);

  std::cout << "Remove 10" << std::endl;
  heap.remove(10);
  printHeap(heap);

  std::cout << "Remove 8" << std::endl;
  heap.remove(8);
  printHeap(heap);

  std::cout << "Peek: " << heap.peek() << std::endl;
  std::cout << "Is empty: " << std::boolalpha << heap.isEmpty() << std::endl;
  std::cout << "Size: " << heap.size() << std::endl;
  std::cout << "Capacity: " << heap.capacity() << std::endl;

  return 0;
}