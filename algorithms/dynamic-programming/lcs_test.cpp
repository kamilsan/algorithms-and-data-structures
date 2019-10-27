#include <iostream>

#include "declarations.hpp"

int main()
{
  std::string word1 = "zxfgdzuzabbcms";
  std::string word2 = "xcabdcs";
  std::cout << "Longest common subsequence of " << "\"" << word1 << "\"" << 
    " and " << "\"" << word2 << "\"" << " is " 
      << "\"" << lcs(word1, word2) << "\"" << std::endl;

  return 0;
}