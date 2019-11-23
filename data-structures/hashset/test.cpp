#include <iostream>
#include <string>
#include <vector>

#include "hashset.hpp"

int main()
{
  std::vector<int> nums = {34, 12, 53, 2, 5, 21, 1, 23, 9, 10, 44, 7, 17};
  const int target = 19;

  std::cout << "[";
  for(unsigned i = 0; i < nums.size(); ++i)
  {
    std::cout << nums[i];
    if(i < nums.size() - 1)
      std::cout << " ";
  }
  std::cout << "]" << std::endl;
  std::cout << "Looking for pairs of numbers that sum up to " << target << "..." << std::endl;

  Hashset<int> complements;
  for(int num : nums)
  {
    int complement = target - num;
    if(complements.contains(complement))
    {
      std::cout << "Found pair: " << complement << ", " << num << std::endl;
    }
    else
      complements.insert(num);
  }

  return 0;
}