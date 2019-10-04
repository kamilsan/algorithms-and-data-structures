#include <iostream>

#include "dynamic-array.hpp"

void printDA(const DynamicArray<int>& arr)
{
  std::cout << "[";
  for(size_t i = 0; i < arr.size(); ++i)
  {
    std::cout << arr[i];
    if(i != arr.size() - 1) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

void printDAInfo(const DynamicArray<int>& arr)
{
  std::cout << "Size: " << arr.size() << " Capacity: " << arr.capacity() << std::boolalpha << " empty: " << arr.isEmpty() << std::endl;
}

int main()
{
  constexpr int capacity = 6;
  DynamicArray<int> array(capacity);
  std::cout << "Created array of size " << array.capacity() << std::endl;
  std::cout << "Size: " << array.size() << std::boolalpha << " empty: " << array.isEmpty() << std::endl;

  constexpr int N = 11;
  int elements[N] = {5, 10, 2, -12, 2, 1, 5, 7, 0, 42, 13};

  for(int i = 0; i < N; ++i)
  {
    std::cout << std::endl << "Inserting element " << elements[i] << "..." << std::endl;
    array.insert(elements[i]);
    printDA(array);
    printDAInfo(array);
  }

  return 0;
}