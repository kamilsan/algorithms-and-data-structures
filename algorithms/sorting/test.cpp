#include <iostream>
#include <chrono>
#include <random>

#include "selection-sort/selectionSort.hpp"
#include "bubble-sort/bubbleSort.hpp"
#include "insertion-sort/insertionSort.hpp"
#include "merge-sort/mergeSort.hpp"
#include "shell-sort/shellSort.hpp"

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
  constexpr unsigned numElements = 1'000'00;
  std::vector<int> nums(numElements);
  std::cout << "Array size: " << numElements << std::endl;
  
  std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(-100, 100);
  auto rng = std::bind(dist, std::ref(generator));

  auto sortingMethods = {
      std::make_pair("Bubble sort", bubbleSort<int>),
      std::make_pair("Selection sort", selectionSort<int>),
      std::make_pair("Insertion sort", insertionSort<int>),
      std::make_pair("Merge sort", mergeSort<int>),
      std::make_pair("Shell sort", shellSort<int>)
    };
  
  for(auto method : sortingMethods)
  {
    randomizeVector(numElements, nums, rng);
    std::cout << "Measuring " << method.first << " performance..." << std::endl;
    auto then = std::chrono::steady_clock::now();
    method.second(nums);
    std::chrono::duration<double> duration = std::chrono::steady_clock::now() - then;
    std::cout << method.first << " took " << duration.count() << "s" << std::endl;
  }

  return 0;
}