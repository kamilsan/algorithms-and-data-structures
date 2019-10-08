#include <iostream>

#include "heap.hpp"

template <typename T>
void printHeap(const Heap<T>& heap)
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
  Heap<int> heap;
  heap.insert(2);
  heap.insert(5);
  heap.insert(-1);
  heap.insert(3);
  heap.insert(4);
  printHeap(heap);
  std::cout << "Size: " << heap.size() << ", capacity: " << heap.capacity() << std::endl;
  std::cout << "Peek: " << heap.peek() << std::endl;

  std::cout << "Pop..." << std::endl;
  heap.pop();
  printHeap(heap);

  heap.contains(5) ? std::cout << "Heap contains 5." : std::cout << "Heap does not contain 5.";
  std::cout << std::endl;
  heap.contains(42) ? std::cout << "Heap contains 42." : std::cout << "Heap does not contain 42.";
  std::cout << std::endl;

  heap.insert(43);
  heap.insert(0);
  heap.insert(3);
  heap.insert(7);
  heap.insert(15);
  printHeap(heap);

  std::cout << "Peek: " << heap.peek() << std::endl;

  std::cout << "Remove 3" << std::endl;
  heap.remove(3);
  printHeap(heap);

  std::cout << "Remove 0" << std::endl;
  heap.remove(0);
  printHeap(heap);

  std::cout << "Remove 7" << std::endl;
  heap.remove(7);
  printHeap(heap);

  std::cout << "Peek: " << heap.peek() << std::endl;
  std::cout << "Is empty: " << std::boolalpha << heap.isEmpty() << std::endl;
  std::cout << "Size: " << heap.size() << std::endl;
  std::cout << "Capacity: " << heap.capacity() << std::endl;

  return 0;
}