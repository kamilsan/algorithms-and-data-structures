#include <iostream>

#include "declarations.hpp"

int main()
{
  std::vector<int> seq = {4, -2, 5, 2, 5, 7, 2, 5, 7, 10, 12, 8};
  auto answer = lis(seq);

  std::cout << "Longest increasing subsequence in:" << std::endl;
  for(unsigned i = 0; i < seq.size(); ++i)
  {
    std::cout << seq[i];
    if(i < seq.size() - 1) std::cout << ", ";
  }

  std::cout << std::endl << "is: " << std::endl;
  for(unsigned i = 0; i < answer.size(); ++i)
  {
    std::cout << answer[i];
    if(i < answer.size() - 1) std::cout << ", ";
  }
  std::cout << std::endl;

  return 0;
}