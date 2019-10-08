#include <iostream>
#include <chrono>
#include <random>

#include "selection-sort/selectionSort.hpp"
#include "bubble-sort/bubbleSort.hpp"

void randomizeVector(unsigned n, std::vector<int>& v, std::function<int()> rng)
{
  v.clear();
  v.reserve(n);
  for(unsigned i = 0; i < n; ++i)
  {
    v.push_back(rng());
  }
}

int main()
{
  std::vector<int> nums;
  constexpr unsigned numElements = 1'000'00;
  std::cout << "Array size: " << numElements << std::endl;
  
  std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(-100, 100);
  auto rng = std::bind(dist, std::ref(generator));
  
  randomizeVector(numElements, nums, rng);
  std::cout << "Measuring bubble sort performance..." << std::endl;
  auto then = std::chrono::steady_clock::now();
  bubbleSort(nums);
  std::chrono::duration<double> duration = std::chrono::steady_clock::now() - then;
  std::cout << "Bubble sort took " << duration.count() << "s" << std::endl;

  randomizeVector(numElements, nums, rng);
  std::cout << "Measuring selection sort performance..." << std::endl;
  then = std::chrono::steady_clock::now();
  selectionSort(nums);
  duration = std::chrono::steady_clock::now() - then;
  std::cout << "Selection sort took " << duration.count() << "s" << std::endl;

  return 0;
}