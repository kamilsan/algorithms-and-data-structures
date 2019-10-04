#include <iostream>
#include <chrono>
#include <random>

#include "selection-sort.hpp"

int main()
{
  std::vector<int> nums = {64, 23, 1, 5, 3, 6, 7, 8, 14, 3, -2, 5, 0};
  for(int n : nums)
  {
    std::cout << n << " ";
  }
  std::cout << std::endl;
  selectionSort(nums);

  for(int n : nums)
  {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  constexpr unsigned numElements = 1'000'00;
  nums.clear();
  nums.reserve(numElements);

  std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(-100, 100);
  for(unsigned i = 0; i < numElements; ++i)
  {
    nums.push_back(dist(generator));
  }
  
  std::cout << "Measuring algorithm performance..." << std::endl;
  auto then = std::chrono::steady_clock::now();
  selectionSort(nums);
  std::chrono::duration<double> duration = std::chrono::steady_clock::now() - then;
  
  std::cout << "Sorting " << numElements << " numbers using selection sort took " << duration.count() << "s" << std::endl;

  return 0;
}