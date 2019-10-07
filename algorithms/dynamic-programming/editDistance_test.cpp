#include <iostream>

#include "declarations.hpp"

int main()
{
  std::string word1 = "palingenesia";
  std::string word2 = "ungenerous";
  int dist = editDistance(word1, word2);
  std::cout << "Edit distance between " << word1 
    << " and " << word2 << " is equal to " << dist << std::endl;

  return 0;
}