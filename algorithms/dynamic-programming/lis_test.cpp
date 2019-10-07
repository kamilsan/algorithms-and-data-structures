#include <iostream>

#include "declarations.hpp"

int main()
{
  std::vector<int> seq = {4, -2, 5, 2, 5, 7, 2, 5, 7, 10, 12, 8};
  int lisLen = lis(seq);
  std::cout << "Longest increasing subsequance in ";

  for(unsigned i = 0; i < seq.size(); ++i)
  {
    std::cout << seq[i];
    if(i < seq.size() - 1) std::cout << ", ";
  }

  std::cout << " has length of " << lisLen << std::endl;

  return 0;
}